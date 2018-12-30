using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WinScoutLib;
using WinScoutNativeWrapper;
using Newtonsoft.Json;

namespace WinScoutConsole {
    class Program {
        static void Main(string[] args) {
            // Get a list of installed products
            InstalledProductsCollection installedProductsCollection = new InstalledProductsCollection();
            installedProductsCollection.EnumInstalledProducts();

            Console.WriteLine($"Found {installedProductsCollection.Count} installed products.");

            // Serialize as json to the console
            Console.WriteLine(JsonConvert.SerializeObject(installedProductsCollection.ToList(), Formatting.Indented));
        }
    }
}