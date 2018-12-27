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
            InstalledProductsCollection installedProductsController = new InstalledProductsCollection();
            List<InstalledProduct> installedProducts = installedProductsController.EnumInstalledProducts();

            // Serialize as json to the console
            Console.WriteLine(JsonConvert.SerializeObject(installedProducts, Formatting.Indented));
        }
    }
}