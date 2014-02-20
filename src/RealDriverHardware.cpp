#include "RealDriverHardware.h"

RealDriverHardware::RealDriverHardware() :
	leftJoystick(1),
	rightJoystick(2)
{ }

RealDriverHardware::~RealDriverHardware() { }

GenericHID& RealDriverHardware::GetLeftJoystick()
{
	return leftJoystick;
}

GenericHID& RealDriverHardware::GetRightJoystick()
{
	return rightJoystick;
}
