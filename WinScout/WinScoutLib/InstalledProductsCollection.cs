using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Microsoft.Win32;

// Class for gathering a list of installed products
// from a variety of sources including MSI APIs, WMI, and the registry 

// Based on ideas from
// http://www.vbforums.com/showthread.php?598355-Example-of-how-to-get-a-list-of-installed-programs-(like-Add-and-Remove-Programs)
// https://social.msdn.microsoft.com/Forums/en-US/94c2f14d-c45e-4b55-9ba0-eb091bac1035/c-get-installed-programs

namespace WinScoutLib {
    public class InstalledProductsCollection : IEnumerable<InstalledProduct>, IEnumerator<InstalledProduct> {

        #region Declarations

        // List of locations to look for installed software
        private readonly string _registryLocation32 = @"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall";
        private readonly string _registryLocation64 = @"SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall";

        #endregion


        #region Properties

        // The dictionary containing the installed products
        protected Dictionary<string, InstalledProduct> InstalledProducts { get; }

        protected int Position { get; set; }

        public int Count => InstalledProducts.Count;

        #endregion Properties

        #region Public Methods

        // Default constructor
        public InstalledProductsCollection() {
            InstalledProducts = new Dictionary<string, InstalledProduct>();
            Reset();
        }

        // Returns a list of installed products, using multiple APIs to fill in the details
        public void EnumInstalledProducts() {
            AddInstalledProductsFromRegistry(Registry.CurrentUser, _registryLocation32);
            AddInstalledProductsFromRegistry(Registry.LocalMachine, _registryLocation32);
            AddInstalledProductsFromRegistry(Registry.LocalMachine, _registryLocation64);
        }

        public IEnumerator<InstalledProduct> GetEnumerator() {
            return this;
        }
        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();

        public InstalledProduct Current {
            get {
                try {
                    return InstalledProducts.Values.ToArray()[Position];
                }
                catch (IndexOutOfRangeException) {
                    throw new InvalidOperationException();
                }
            }
        }

        object IEnumerator.Current => Current;

        public bool MoveNext() {
            Position++;
            return (Position < InstalledProducts.Values.Count);
        }

        public void Reset() {
            Position = -1;
        }

        public void Dispose() { }

        public List<InstalledProduct> ToList() {
            return InstalledProducts.Values.ToList();
        }

        #endregion Public Methods

        #region Private Methods

        // Try to find the list of installed products at the given registry key
        private void AddInstalledProductsFromRegistry(RegistryKey rootKey, string subKey) {
            RegistryKey productsKey = rootKey.OpenSubKey(subKey);
            if (productsKey != null) {
                foreach (string keyName in productsKey.GetSubKeyNames()) {
                    // Find the existing product to update, or add if needed
                    InstalledProduct installedProduct;
                    if (InstalledProducts.ContainsKey(keyName)) {
                        installedProduct = InstalledProducts[keyName];
                    }
                    else {
                        installedProduct = new InstalledProduct {
                            ProductCode = keyName
                        };
                        InstalledProducts.Add(keyName, installedProduct);
                    }

                    // Read the properties of the product from the subkeys
                    UpdateInstalledProductFromRegistryKey(productsKey.OpenSubKey(keyName), installedProduct);
                }
            }
        }

        // Try to extract product information from the given registry key
        private void UpdateInstalledProductFromRegistryKey(RegistryKey productKey, InstalledProduct installedProduct) {
            installedProduct.RegistryLocations.Add(productKey.ToString());

            // Loop through the properties in installed product and try to find the corresponding registry value
            PropertyInfo[] properties = installedProduct.GetType().GetProperties();

            foreach (PropertyInfo propertyInfo in properties) {
                // Should this property by ignored
                RegistryValueIgnore ignoreAttribute = (RegistryValueIgnore)propertyInfo.GetCustomAttribute(typeof(RegistryValueIgnore));
                if (ignoreAttribute?.Ignore != true) {
                    // Are there multiple registry values we should check for this property?
                    RegistryValue[] valueAttributes = (RegistryValue[])propertyInfo.GetCustomAttributes(typeof(RegistryValue));

                    if (valueAttributes?.Length > 0) {
                        foreach (RegistryValue valueAttribute in valueAttributes) {
                            if (productKey.GetValueNames().Contains(valueAttribute.Value)) {
                                SetInstalledProductPropertyFromRegistryValue(productKey, installedProduct, propertyInfo, valueAttribute.Value);
                                break;
                            }
                        }
                    }
                    else {
                        // Use the name of the property as the name of the registry value
                        SetInstalledProductPropertyFromRegistryValue(productKey, installedProduct, propertyInfo, propertyInfo.Name);
                    }
                }
            }
        }

        private void SetInstalledProductPropertyFromRegistryValue(RegistryKey productKey, InstalledProduct installedProduct, PropertyInfo propertyInfo, string registryValue) {
            switch (propertyInfo?.PropertyType?.Name) {
                case "String":
                    propertyInfo.SetValue(installedProduct, productKey.GetValueAsString(registryValue));
                    break;
                case "Int32":
                    propertyInfo.SetValue(installedProduct, productKey.GetValueAsInt32(registryValue));
                    break;
                case "Boolean":
                    propertyInfo.SetValue(installedProduct, productKey.GetValueAsBoolean(registryValue));
                    break;
                default:
                    break;
            }
        }

        #endregion
    }
}