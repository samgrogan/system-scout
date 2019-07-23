#include "DeviceDriver.h"

using namespace WinScout::Interop;
using namespace Managed;

DeviceDriver::DeviceDriver(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{
	if (UMDriver == nullptr)
	{
		throw gcnew System::Exception("Can't create a managed Driver from a nullptr");
	}
}
