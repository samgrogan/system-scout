using System;
using System.Collections.Generic;
using System.Text;

namespace WinScout.Core {
    [System.AttributeUsage(System.AttributeTargets.Property, AllowMultiple = true)]
    public class RegistryValue : System.Attribute {
        public string Value { get; set; }

        public RegistryValue(string value) {
            Value = value;
        }
    }

    [System.AttributeUsage(System.AttributeTargets.Property)]
    public class RegistryValueIgnore : System.Attribute {
        public bool Ignore { get; set; }

        public RegistryValueIgnore(bool ignore) {
            Ignore = ignore;
        }
    }
}