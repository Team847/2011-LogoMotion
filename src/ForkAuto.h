#ifndef FORKAUTO_H
#define FORKAUTO_H

#define SMART_START_TIME 2
#define SMART_END_TIME 3
#define SPEED_MULTIPLIER 0.3f

#include "AutonomousMode.h"
#include "GyroOrient.h"

class ForkAuto : public AutonomousMode
{
public:
	enum Mode
	{
		Straight,
		Left,
		Right,
		Smart
	};
	
	ForkAuto(RobotHardware& robot, Mode mode);
	virtual ~ForkAuto();
	virtual void Periodic();
	
private:
	enum State
	{
		TrackingLine,
		PlacingTube,
		MovingToCenter,
		Finished
	};
	
	State state;
	bool isSmart;
	Timer timer;
	GyroOrient orient;
};

#endif
