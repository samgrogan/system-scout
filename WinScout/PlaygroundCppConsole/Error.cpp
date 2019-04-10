#include "Error.h"

using namespace playground;

// Construct an error based on GetLastError
Error::Error()
{
	void* format_message_buffer = nullptr;

	// Get and format the error message
	DWORD last_error = GetLastError();
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		last_error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(wchar_t*)&format_message_buffer,
		0, NULL);

	// Display the error message and exit the process
	const std::wstring display_buffer = L"Last error was " + std::to_wstring(last_error) + L": " + static_cast<wchar_t*>(format_message_buffer);
	OutputDebugString(display_buffer.c_str());

	LocalFree(format_message_buffer);
}


Error::~Error()
{
}
