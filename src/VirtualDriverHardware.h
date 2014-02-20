#ifndef VIRTUALDRIVERHARDWARE_H
#define VIRTUALDRIVERHARDWARE_H

#include "DriverHardware.h"
#include "RecordedJoystick.h"

class VirtualDriverHardware : public DriverHardware
{
public:
	VirtualDriverHardware(const char* leftFilename, const char* rightFilename);
	virtual ~VirtualDriverHardware();
	virtual GenericHID& GetLeftJoystick();
	virtual GenericHID& GetRightJoystick();
	void Start();
	void Stop();
	void Reset();
	
private:
	RecordedJoystick leftJoystick, rightJoystick;
};

#endif
