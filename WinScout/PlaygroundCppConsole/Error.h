#pragma once

#include <string>
#include <iostream>

#include <windows.h>

namespace playground {

	class Error
	{
	private:
		DWORD _last_error;

	public:
		// Construct an error based on GetLastError
		Error();

		// Writes the error message to the debug console
		void OutputToDebugger();

		// Gets the error code
		DWORD GetErrorCode();

		// Gets the error message
		std::wstring GetErrorMessage();

		virtual ~Error();
	};

}