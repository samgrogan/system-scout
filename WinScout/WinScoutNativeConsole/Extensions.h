#pragma once

#include <iostream>

#include <Windows.h>
#include <Rpcdce.h>
#include <SetupAPI.h>
#include <Devpropdef.h>
#include <Devpkey.h>

// Output a GUID as a formatted string
std::wostream& operator<<(std::wostream& wos, REFGUID guid);

bool operator==(DEVPROPKEY& left, DEVPROPKEY& right);

namespace std
{
	template<>
	struct hash<GUID>
	{
		size_t operator()(const GUID& value) const
		{
			RPC_STATUS status = RPC_S_OK;
			return ::UuidHash(&const_cast<GUID&>(value), &status);
		}
	};


	template<>
	struct hash<DEVPROPKEY>
	{
		size_t operator()(const DEVPROPKEY& value) const
		{
			size_t const h1 = std::hash<GUID>{}(value.fmtid);
			return h1;
		}
	};
}