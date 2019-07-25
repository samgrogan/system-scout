using System;
using System.Collections.Generic;
using System.Diagnostics;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using WinScout.Interop.Managed;

namespace WinScout.Test {
    [TestClass]
    public class DeviceEnumeratorTest {
        [TestMethod]
        public void EnumerateDevices() {
            Stopwatch sw = Stopwatch.StartNew();

            // Create a device enumerator
            DeviceEnumerator de = new DeviceEnumerator();

            // Get the list of all devices
            List<Device> devices = de.EnumerateDevices();

            sw.Stop();

            // Display the results
            Console.WriteLine($"Completed in {sw.ElapsedMilliseconds}ms.");
            Console.WriteLine($"Found {devices.Count} devices.");

            foreach (Device device in devices) {
                Debug.Assert(!string.IsNullOrWhiteSpace(device.DeviceId), "Device ID cannot be blank");

                Console.WriteLine();
                Console.WriteLine($"\tDevice ID:\t{device.DeviceId}");
                Console.WriteLine($"\tHardware Ids:\t{String.Join(",", device.HardwareIds)}");
                Console.WriteLine($"\tCompatible Ids:\t{String.Join(",", device.CompatibleIds)}");
                Console.WriteLine($"\tName:\t\t{device.Name}");
                Console.WriteLine($"\tDescription:\t{device.Description}");
                Console.WriteLine($"\tManufacturer:\t{device.Manufacturer}");
                Console.WriteLine($"\tType:\t\t{device.Type}");
                Console.WriteLine($"\tClass GUID:\t{device.ClassGuid}");

                // Get the list of drivers for this device
                List<DeviceDriver> drivers = device.Drivers;
                Console.WriteLine($"\t\tFound {drivers.Count} drivers.");

                foreach (DeviceDriver driver in drivers) {
                    Console.WriteLine();
                    Console.WriteLine($"\t\t\tHardware Ids:\t{String.Join(",", driver.HardwareIds)}");
                    Console.WriteLine($"\t\t\tDescription:\t{driver.Description}");
                    Console.WriteLine($"\t\t\tManufacturer:\t{driver.Manufacturer}");
                    Console.WriteLine($"\t\t\tVersion:\t{driver.Version}");
                    Console.WriteLine($"\t\t\tRelease Date:\t{driver.ReleaseDate}");
                    Console.WriteLine($"\t\t\tINF File:\t{driver.InfFile}");
                }
            }

        }
    }
}
