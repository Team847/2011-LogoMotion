#ifndef TELEOPMECANUM_H
#define TELEOPMECANUM_H

#define MANIPLOWBUTTON 3
#define MANIPFLOORBUTTON 2
#define MANIPHIGHBUTTON 4
#define MANIPSLOTBUTTON 5
#define MANIPCARRYBUTTON 6
#define MANIPMINIDEPLOY 8
#define MANIPCLAW 1
#define MANIPRESET 7

#define DRIVECLAW 1
#define DRIVEGYROBUTTON 2
#define DRIVEBUSHBUTTON 3 //BUSH means mulberry bush assist

#include "TeleopMode.h"
#include "GyroOrient.h"
#include "MulberryBush.h"
#include <Math.h>

class TeleopMecanum : public TeleopMode
{
public:
	TeleopMecanum (RobotHardware& robot, DriverHardware& driver);
	virtual ~TeleopMecanum();
	virtual void Periodic();
private:
	DigitalInput autodrive;
	bool FinishAuto;
	Timer timer;
	GyroOrient orient;
	bool DriveTrigger;
	bool ManipTrigger;
	bool MiniDeploy;
	bool Xzero;
	bool Yzero;
	bool Zzero;
	MulberryBush bush;
	float TwistReduce(float input);
	float Magnitude(GenericHID& joystick);
	float Direction(GenericHID& joystick);
};

#endif
