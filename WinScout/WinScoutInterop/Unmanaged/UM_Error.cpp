#include "UM_Error.h"

using namespace WinScout::Interop::Unmanaged;

// Construct an error based on GetLastError
Error::Error()
{
	// Get and format the error message
	_last_error = GetLastError();
}

// Gets the error code
DWORD Error::GetErrorCode() const
{
	return _last_error;
}

// Gets the error message
std::wstring Error::GetErrorMessage() const
{
	void* format_message_buffer = nullptr;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		_last_error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<wchar_t*>(&format_message_buffer),
		0, nullptr);

	// Convert to a wstring
	const std::wstring display_buffer = L"Last error was " + std::to_wstring(_last_error) + L": " + static_cast<wchar_t*>(format_message_buffer);
	LocalFree(format_message_buffer);

	return display_buffer;
}

Error::~Error()
= default;
