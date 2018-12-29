using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
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
        private string _registryLocation32 = @"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall";
        private string _registryLocation64 = @"SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall";

        #endregion


        #region Properties

        // The dictionary containing the installed products
        protected Dictionary<string, InstalledProduct> InstalledProducts { get; }

        protected int Position { get; set; }

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


        #endregion Public Methods

        #region Private Methods

        private void AddInstalledProductsFromRegistry(RegistryKey rootKey, string subKey) {
            RegistryKey productsKey = rootKey.OpenSubKey(subKey);
            if (productsKey != null) {

            }
        }

        // Adds the given list of Msi Api installed products to the list of all installed products
        private void AddMsiApiInstalledProducts(List<MsiInstalledProduct> msiInstalledProducts) {
            //foreach (MsiInstalledProduct msiInstalledProduct in msiInstalledProducts) {
            //    // Do we already have information on this product?
            //    string productCode = msiInstalledProduct.ProductCode;

            //    InstalledProduct installedProduct = InstalledProducts.ContainsKey(productCode) ? InstalledProducts[productCode] : new InstalledProduct();
            //    installedProduct.ProductCode = productCode;
            //    installedProduct.DisplayName = msiInstalledProduct.ProductName;
            //    installedProduct.DisplayVersion = msiInstalledProduct.ProductVersion;
            //    installedProduct.InstallDate = msiInstalledProduct.InstallDate;
            //    installedProduct.InstallLocation = msiInstalledProduct.InstallLocation;
            //    installedProduct.InstallSource = msiInstalledProduct.InstallSource;
            //    installedProduct.LocalPackage = msiInstalledProduct.LocalPackage;
            //    installedProduct.PackageName = msiInstalledProduct.PackageName;
            //    installedProduct.PackageCode = msiInstalledProduct.PackageCode;
            //    installedProduct.Language = msiInstalledProduct.Language;
            //    installedProduct.Publisher = msiInstalledProduct.Publisher;

            //    if (!InstalledProducts.ContainsKey(productCode)) {
            //        InstalledProducts.Add(productCode, installedProduct);
            //    }
            //}
        }

        #endregion
    }
}