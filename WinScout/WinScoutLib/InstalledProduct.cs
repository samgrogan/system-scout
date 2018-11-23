using System;
using System.Collections.Generic;
using System.Text;

// Represents a single installed product (software application)

namespace WinScoutLib {

    public class InstalledProduct {
        // The unique product code (GUID) that represents this product
        public string ProductCode { get; set; }

        // The name of the product
        public string DisplayName { get; set; }

        // The version (string)
        public string DisplayVersion { get; set; }
    }
}