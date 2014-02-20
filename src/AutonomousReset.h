#ifndef TELEOPRESET_H
#define TELEOPRESET_H

#include "AutonomousMode.h"

class AutonomousReset : public AutonomousMode
{
public:
	AutonomousReset(RobotHardware& robot);
	virtual void Periodic();
};

#endif
