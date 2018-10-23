using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace WinScoutLib.PInvoke
{
    class CfgMgr
    {
        [DllImport("cfgmgr32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern void CM_Enumerate_Classes(
            [In] ulong         ulClassIndex,
        [Out]  Guid        ClassGuid,
        [In] ulong         ulFlags
        );
    }
}
