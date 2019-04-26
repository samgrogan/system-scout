#include "Error.h"

using namespace playground;

// Construct an error based on GetLastError
Error::Error()
{
	// Get and format the error message
	_last_error = GetLastError();

	// Output the error message to the debugger
	OutputToDebugger();
}

// Writes the error message to the debug console
void Error::OutputToDebugger() {
	void* format_message_buffer = nullptr;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		_last_error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(wchar_t*)& format_message_buffer,
		0, NULL);

	// Display the error message and exit the process
	const std::wstring display_buffer = L"Last error was " + std::to_wstring(_last_error) + L": " + static_cast<wchar_t*>(format_message_buffer);
	OutputDebugString(display_buffer.c_str());

	std::wcout << "\t" << display_buffer;

	LocalFree(format_message_buffer);
}

// Gets the error code
DWORD Error::GetErrorCode() {
	return _last_error;
}

Error::~Error()
{
}
