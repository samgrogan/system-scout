using System;
using WinScoutNativeWrapper;
using System.Collections.Generic;
using System.Linq;

// Class for gathering a list of installed products
// from a variety of sources including MSI APIs, WMI, and the registry 

namespace WinScoutLib {

    public class InstalledProductsCollection {

        #region Properties

        // The dictionary containing the installed products
        protected Dictionary<string, InstalledProduct> InstalledProducts { get; }

        #endregion Properties

        #region Public Methods

        // Default constructor
        public InstalledProductsCollection() {
            InstalledProducts = new Dictionary<string, InstalledProduct>();
        }

        // Returns a list of installed product
        public List<InstalledProduct> EnumInstalledProducts() {
            // Get the list of installed products from the MSI API
            MsiApiEnumInstalledProducts();

            // Return the list of installed products
            return InstalledProducts.Values.ToList();
        }

        #endregion Public Methods

        // Returns a list of installed products using the MSI API
        private void MsiApiEnumInstalledProducts() {
            // Get the list of installed products from the MSI API
            MsiApiWrapper msiApiWrapper = new MsiApiWrapper();

            List<MsiInstalledProduct> msiInstalledProducts = msiApiWrapper.EnumInstalledProducts();

            foreach (MsiInstalledProduct msiInstalledProduct in msiInstalledProducts) {
                // Do we already have information on this product?
                string productCode = msiInstalledProduct.ProductCode;

                InstalledProduct installedProduct = InstalledProducts.ContainsKey(productCode) ? InstalledProducts[productCode] : new InstalledProduct();
                installedProduct.Source |= InstalledProductSource.MsiApi;
                installedProduct.ProductCode = productCode;
                installedProduct.DisplayName = msiInstalledProduct.ProductName;
                installedProduct.DisplayVersion = msiInstalledProduct.ProductVersion;
                installedProduct.InstallDate = msiInstalledProduct.InstallDate;
                installedProduct.Publisher = msiInstalledProduct.Publisher;

                if (!InstalledProducts.ContainsKey(productCode)) {
                    InstalledProducts.Add(productCode, installedProduct);
                }
            }
        }
    }
}