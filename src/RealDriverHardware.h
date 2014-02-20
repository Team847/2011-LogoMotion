#ifndef REALDRIVERHARDWARE_H
#define REALDRIVERHARDWARE_H

#include "DriverHardware.h"

class RealDriverHardware : public DriverHardware
{
public:
	RealDriverHardware();
	virtual ~RealDriverHardware();
	virtual GenericHID& GetLeftJoystick();
	virtual GenericHID& GetRightJoystick();
	
private:
	Joystick leftJoystick, rightJoystick;
};

#endif
