#pragma once

#include <string>

class ComplexClass
{
private:
	std::wstring _value;

public:

	std::wstring GetValue();

	ComplexClass();
	~ComplexClass();
};

