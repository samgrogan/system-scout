using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Win32;

namespace WinScout.Core {
    public static class RegistryKeyExtensions {
        public static string GetValueAsString(this RegistryKey parentKey, string valueName) {
            return parentKey?.GetValue(valueName)?.ToString();
        }

        public static UInt32? GetValueAsInt32(this RegistryKey parentKey, string valueName) {
            return parentKey?.GetValue(valueName) as UInt32?;
        }

        public static bool GetValueAsBoolean(this RegistryKey parentKey, string valueName) {
            return (parentKey?.GetValue(valueName)?.ToString() == "1") ? true : false;
        }

    }
}