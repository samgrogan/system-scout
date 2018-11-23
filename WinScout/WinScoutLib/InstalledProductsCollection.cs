using System;
using WinScoutNativeWrapper;
using System.Collections.Generic;

// Class for gathering a list of installed products
// from a variety of sources including MSI APIs, WMI, and the registry 

namespace WinScoutLib {

    // Where was this product detected?
    public enum InstalledProductSource : byte {
        Unknown = 0x00,
        MsiApi = 0x01, // From the MSI API
        Win32Product = 0x02, // From the WMI / Win32_Product
        RegistryUninstall = 0x04 // From the registry in HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Uninstall
    }

    public class InstalledProductsCollection {

        // The dictionary containing the installed products
        protected Dictionary<string, >



        // Returns a list of installed product
        public List<InstalledProduct> EnumInstalledProducts() {
            MsiApiWrapper msiApiWrapper = new MsiApiWrapper();
            List<InstalledProduct> installedProducts = msiApiWrapper.EnumInstalledProducts();

            return installedProducts;
        }
    }
}