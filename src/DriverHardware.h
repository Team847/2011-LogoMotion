#ifndef DRIVERHARDWARE_H
#define DRIVERHARDWARE_H

#include "WPILib.h"

class DriverHardware
{
public:
	virtual GenericHID& GetLeftJoystick() = 0;
	virtual GenericHID& GetRightJoystick() = 0;
};

#endif
