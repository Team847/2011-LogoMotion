#include "VirtualDriverHardware.h"

VirtualDriverHardware::VirtualDriverHardware(const char* leftFilename, const char* rightFilename) :
	leftJoystick(leftFilename),
	rightJoystick(rightFilename)
{ }

VirtualDriverHardware::~VirtualDriverHardware() { }

GenericHID& VirtualDriverHardware::GetLeftJoystick()
{
	return leftJoystick;
}

GenericHID& VirtualDriverHardware::GetRightJoystick()
{
	return rightJoystick;
}

void VirtualDriverHardware::Start()
{
	leftJoystick.Start();
	rightJoystick.Start();
}

void VirtualDriverHardware::Stop()
{
	leftJoystick.Stop();
	rightJoystick.Stop();
}

void VirtualDriverHardware::Reset()
{
	leftJoystick.Reset();
	rightJoystick.Reset();
}
