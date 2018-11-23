#include "stdafx.h"
#include "../WinScoutNativeWrapperLib/MsiApiWrapper.h"

using namespace WinScoutNativeWrapper;


int main(array<System::String ^>^ args) {
	try {
		MsiApiWrapper^ msiApiWrapper = gcnew MsiApiWrapper();
	}
	catch (Exception ^ex) {
		Console::WriteLine(ex);
	}

	return 0;
}
