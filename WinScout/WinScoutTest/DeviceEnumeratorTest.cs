using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using WinScout.Interop.Managed;

namespace WinScout.Test {
    [TestClass]
    public class DeviceEnumeratorTest {
        [TestMethod]
        public void EnumerateDevices() {
            DeviceEnumerator de = new DeviceEnumerator();
            List<Device> devices = de.EnumerateDevices();

            Console.WriteLine($"Found {devices.Count} devices.");

            foreach (Device device in devices) {
                Console.WriteLine($"\t{device.DeviceId}");
            }
        }
    }
}
