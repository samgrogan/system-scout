#pragma once

#include <iostream>
#include <vector>

#include <Windows.h>
#include <cfgmgr32.h>
#include <initguid.h>
#include <Devpropdef.h>
//#include <Devpkey.h>

#include "Error.h"
#include "Extensions.h"
#include "devpkey_description.h"

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
		INT8 _value_sbyte = 0;
		BYTE _value_byte = 0U;
		INT16 _value_int16 = 0;
		UINT16 _value_uint16 = 0U;
		INT32 _value_int32 = 0;
		UINT32 _value_uint32 = 0U;
		INT64 _value_int64 = 0L;
		UINT64 _value_uint64 = 0UL;
		FLOAT _value_float = 0.0;
		DOUBLE _value_double = 0.0L;
		DECIMAL _value_decimal{};
		GUID _value_guid{};
		CURRENCY _value_currency{};
		DATE _value_date{};
		FILETIME _value_filetime{};
		BOOLEAN _value_boolean = 0U;
		std::wstring _value_string{};
		std::vector<std::wstring> _value_string_list;
		SECURITY_DESCRIPTOR _value_security_descriptor{};
		NTSTATUS _value_ntstatus = 0L;
		UINT32 _value_error = 0U;

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