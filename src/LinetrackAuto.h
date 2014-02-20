#ifndef LINETRACKAUTO_H
#define LINETRACKAUTO_H

#include "AutonomousMode.h"

class LinetrackAuto : public AutonomousMode
{
public:
	LinetrackAuto(RobotHardware& robot);
	virtual ~LinetrackAuto();
	virtual void Periodic();
	
private:
	Timer timer;
	Timer backTimer;
	int Move, BackForward;
};

#endif
