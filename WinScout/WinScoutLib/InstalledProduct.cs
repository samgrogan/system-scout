using System;
using System.Collections.Generic;
using System.Text;

// Represents a single installed product (software application)

namespace WinScoutLib {
    // Where was this product detected?
    [Flags]
    public enum InstalledProductSource : byte {
        Unknown = 0x00,
        MsiApi = 0x01, // From the MSI API
        Win32Product = 0x02, // From the WMI / Win32_Product
        RegistryUninstall = 0x04 // From the registry in HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Uninstall
    }

    public class InstalledProduct {

        // The source(s) of information for this product
        public InstalledProductSource Source { get; set; }

        // The unique product code (GUID) that represents this product
        public string ProductCode { get; set; }

        // The name of the product
        public string DisplayName { get; set; }

        // The version (string)
        public string DisplayVersion { get; set; }

        // The date the product was installed, if available
        public DateTime? InstallDate { get; set; }

        // The location where the product is installed
        public string InstallLocation { get; set; }

        // The installation source (usually in the package cache)
        public string InstallSource { get; set; }

        // The local package containing the installer
        public string LocalPackage { get; set; }

        // The name of the package containing this product
        public string PackageName { get; set; }

        // The code for the package containing this product
        public string PackageCode { get; set; }

        // The language of the product
        public string Language { get; set; }

        // The name of the publisher
        public string Publisher { get; set; }
    }
}