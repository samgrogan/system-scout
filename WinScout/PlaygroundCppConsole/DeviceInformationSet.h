#pragma once

#include <Windows.h>
#include <SetupAPI.h>

class DeviceInformationSet
{
private:
	HDEVINFO DeviceInfoSet;

public:
	// Constructor
	// Creates a DeviceInformationSet that includes all devices
	DeviceInformationSet();


	// Desctructor
	virtual ~DeviceInformationSet();
};

