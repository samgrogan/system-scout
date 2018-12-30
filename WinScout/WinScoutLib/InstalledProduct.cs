using System;
using System.Collections.Generic;
using System.Text;

// Represents a single installed product (software application)

namespace WinScoutLib {

    public class InstalledProduct {

        #region Properties

        // The unique product code (GUID) that represents this product
        [RegistryValueIgnore(true)]
        public string ProductCode { get; set; }

        // Locations in the registry where this product was found
        [RegistryValueIgnore(true)]
        public List<string> RegistryLocations { get; set; } = new List<string>();

        // The name of the product
        public string DisplayName { get; set; }

        // The version (string)
        public string DisplayVersion { get; set; }

        // The path to the icon to display
        public string DisplayIcon { get; set; }

        // The estimated size of the product
        public Int32 EstimatedSize { get; set; }

        // The date the product was installed, if available
        public string InstallDate { get; set; }

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

        // The path to modify the installation
        [RegistryValue("ModifyPath")]
        public string ModifyCommand { get; set; }

        // The path to uninstall
        [RegistryValue("UninstallString")]
        public string UninstallCommand { get; set; }

        public bool NoModify { get; set; }

        public bool NoRepair { get; set; }

        #endregion
    }
}