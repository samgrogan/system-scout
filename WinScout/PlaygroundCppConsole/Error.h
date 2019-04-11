#pragma once

#include <windows.h>
#include <string>

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

		virtual ~Error();
	};

}