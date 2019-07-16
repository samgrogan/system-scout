#pragma once

#include <Windows.h>
#include <cfgmgr32.h>
#include <initguid.h>
#include <Devpropdef.h>
//#include <Devpkey.h>

#include "Error.h"
#include "Extensions.h"

namespace WinScoutNativeCore {

	class DevicePropertyBase
	{
	protected:
		// The key to identify this property
		DEVPROPKEY _property_key{};

		// The type of the property
		DEVPROPTYPE _property_type = 0UL;

		// Try to read the value of the property
		virtual void GetPropertyValue() = 0;

		// Parse the property value and convert to the underlying type
		void ParsePropertyValue(ULONG PropertyBufferSize, PBYTE Buffer);

		// The raw value of the property
		std::wstring _value_string{};
		GUID _value_guid{};

	public:

		// Constructor
		DevicePropertyBase(DEVPROPKEY& PropertyKey);

		// Gets the key of this property
		DEVPROPKEY GetKey() const;

		// Gets the type of this property
		DEVPROPTYPE GetType() const;

		// Gets the description of this property
		std::wstring GetDescription() const;

		// Get the string value of this property
		std::wstring GetStringValue() const;

		// Get the GUID value of this property
		REFGUID GetGuidValue() const;

		// Output the value to the given stream
		std::wostream& WriteToStream(std::wostream& wos) const;

		// Destructor
		virtual ~DevicePropertyBase();
	};
}