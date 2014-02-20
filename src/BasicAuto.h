#ifndef BASICAUTO_H
#define BASICAUTO_H

#include "AutonomousMode.h"

class BasicAuto : public AutonomousMode
{
public:
	BasicAuto(RobotHardware& robot);
	virtual void Periodic();
};

#endif
