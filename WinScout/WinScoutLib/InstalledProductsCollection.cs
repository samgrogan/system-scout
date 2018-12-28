using System;
using WinScoutNativeWrapper;
using System.Collections.Generic;
using System.Linq;

// Class for gathering a list of installed products
// from a variety of sources including MSI APIs, WMI, and the registry 

// https://stackoverflow.com/questions/29937568/how-can-i-find-the-product-guid-of-an-installed-msi-setup
// https://stackoverflow.com/questions/46637094/how-can-i-find-the-upgrade-code-for-an-installed-msi-file/46637095#46637095

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

        // Returns a list of installed products, using multiple APIs to fill in the details
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

            // Get products for each of the available contexts
            AddMsiApiInstalledProducts(msiApiWrapper.EnumInstalledProducts(MsiInstalledProductContext.CurrentUser));
            AddMsiApiInstalledProducts(msiApiWrapper.EnumInstalledProducts(MsiInstalledProductContext.AllUsers));
            AddMsiApiInstalledProducts(msiApiWrapper.EnumInstalledProducts(MsiInstalledProductContext.PerMachine));
        }

        // Adds the given list of Msi Api installed products to the list of all installed products
        private void AddMsiApiInstalledProducts(List<MsiInstalledProduct> msiInstalledProducts) {
            foreach (MsiInstalledProduct msiInstalledProduct in msiInstalledProducts) {
                // Do we already have information on this product?
                string productCode = msiInstalledProduct.ProductCode;

                InstalledProduct installedProduct = InstalledProducts.ContainsKey(productCode) ? InstalledProducts[productCode] : new InstalledProduct();
                installedProduct.Source |= InstalledProductSource.MsiApi;
                installedProduct.ProductCode = productCode;
                installedProduct.DisplayName = msiInstalledProduct.ProductName;
                installedProduct.DisplayVersion = msiInstalledProduct.ProductVersion;
                installedProduct.InstallDate = msiInstalledProduct.InstallDate;
                installedProduct.InstallLocation = msiInstalledProduct.InstallLocation;
                installedProduct.InstallSource = msiInstalledProduct.InstallSource;
                installedProduct.LocalPackage = msiInstalledProduct.LocalPackage;
                installedProduct.PackageName = msiInstalledProduct.PackageName;
                installedProduct.PackageCode = msiInstalledProduct.PackageCode;
                installedProduct.Language = msiInstalledProduct.Language;
                installedProduct.Publisher = msiInstalledProduct.Publisher;

                if (!InstalledProducts.ContainsKey(productCode)) {
                    InstalledProducts.Add(productCode, installedProduct);
                }
            }
        }
    }
}