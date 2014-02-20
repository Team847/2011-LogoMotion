#ifndef TELEOPMODE_H
#define TELEOPMODE_H

#include "RobotHardware.h"
#include "DriverHardware.h"

class TeleopMode
{
public:
	TeleopMode(RobotHardware& robot, DriverHardware& driver);
	virtual void Periodic();
	virtual void Continuous();
	
protected:
	RobotHardware& robot;
	DriverHardware& driver;
};

#endif
