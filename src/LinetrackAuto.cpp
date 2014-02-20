#include "LinetrackAuto.h"

LinetrackAuto::LinetrackAuto(RobotHardware& robot) :
	AutonomousMode(robot), timer(), backTimer()
{
	robot.GetLineTracker().SetRoute(LineTracker::Straight);
	robot.GetManip().SetClose(true);
	timer.Start();
	Move = 1;
	BackForward = 0;
}

LinetrackAuto::~LinetrackAuto() { }

void LinetrackAuto::Periodic()
{
	robot.GetManip().SetHighPeg();
	if (BackForward == 0)
	{
		robot.GetDrive().MecanumDrive_Cartesian(robot.GetLineTracker().GetDriveStrafe(), .26 * Move,0);
	}
	if (BackForward == 1)
	{
		robot.GetDrive().MecanumDrive_Cartesian(0,-0.2,0,0);
	}
	
	if (timer.Get() > 8)
		Move = 0;
	
	if (robot.GetLineTracker().IsAtEnd())
	{
		Move = 0;
		robot.GetManip().SetOpen();
		backTimer.Start();
	}
	
	/*if (robot.GetFrontUltrasound().GetVoltage() < 5)
	{
		Move = 0;
		robot.GetManip().SetOpen();
		backTimer.Start();
	}*/
	
	if (backTimer.Get() > .05 && backTimer.Get() < 5)
		BackForward = 1;

	if (backTimer.Get() > 5)
		BackForward = 2;
	//line tracker or "Mode 1"
}
