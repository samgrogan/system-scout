#pragma once

#include <string>
#include <iostream>

#include <windows.h>

namespace WinScoutNativeCore
{
	class Error
	{
	private:
		DWORD _last_error;

	public:
		// Construct an error based on GetLastError
		Error();

		// Gets the error code
		DWORD GetErrorCode() const;

		// Gets the error message
		std::wstring GetErrorMessage() const;

		virtual ~Error();
	};
}
