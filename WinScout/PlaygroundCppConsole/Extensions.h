#pragma once

#include <iostream>

#include <Windows.h>

	
// Output a GUID as a formatted string
std::wostream& operator<<(std::wostream& wos, REFGUID guid);

