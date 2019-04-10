#pragma once

#include <windows.h>
#include <string>

namespace playground {

	class Error
	{
	public:
		// Construct an error based on GetLastError
		Error();
		virtual ~Error();
	};

}