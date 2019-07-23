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

            Console.WriteLine($"Found {devices.Count} devices.");


            foreach (Device device in devices) {
                Debug.Assert(!string.IsNullOrWhiteSpace(device.DeviceId), "Device ID cannot be blank");

                Console.WriteLine();
                Console.WriteLine($"\tDevice ID:\t{device.DeviceId}");
                Console.WriteLine($"\tName:\t\t{device.Name}");
                Console.WriteLine($"\tDescription:\t{device.Description}");
                Console.WriteLine($"\tHardware Ids:\t{String.Join(",", device.HardwareIds)}");
                Console.WriteLine($"\tCompatible Ids:\t{String.Join(",", device.CompatibleIds)}");
                Console.WriteLine($"\tManufacturer:\t{device.Manufacturer}");
                Console.WriteLine($"\tModel:\t{device.Model}");
            }

            sw.Stop();
            Console.WriteLine($"Completed in {sw.ElapsedMilliseconds}ms.");
        }
    }
}
