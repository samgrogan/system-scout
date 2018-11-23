using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WinScoutLib;
using WinScoutNativeWrapper;

namespace WinScoutConsole {
    class Program {
        static void Main(string[] args) {

            // Get a list of installed products
            InstalledProductsController installedProductsController = new InstalledProductsController();
            List<InstalledProduct> installedProducts = installedProductsController.EnumInstalledProducts();

            foreach (InstalledProduct installedProduct in installedProducts) {
                Console.WriteLine($"{installedProduct.ProductCode} : {installedProduct.ProductName}");
            }
        }
    }
}