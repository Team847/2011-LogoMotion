#ifndef AUTONOMOUSMODE_H
#define AUTONOMOUSMODE_H

#include "RobotHardware.h"

class AutonomousMode
{
public:
	AutonomousMode(RobotHardware& robot);
	virtual void Periodic();
	virtual void Continuous();
	
protected:
	RobotHardware& robot;
};

#endif
