using System;
using WinScoutNativeWrapper;
using System.Collections.Generic;

namespace WinScoutLib {
    public class InstalledProductsController {
        // Returns a list of installed product
        public List<InstalledProduct> EnumInstalledProducts() {
            MsiApiWrapper msiApiWrapper = new MsiApiWrapper();
            List<InstalledProduct> installedProducts = msiApiWrapper.EnumInstalledProducts();

            return installedProducts;
        }
    }
}