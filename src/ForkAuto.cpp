#include "ForkAuto.h"

ForkAuto::ForkAuto(RobotHardware& robot, Mode mode) :
	AutonomousMode(robot),
	state(TrackingLine),
	isSmart(mode == Smart),
	timer(),
	orient(robot.GetGyro())
{
	switch (mode)
	{
	case Straight:
		robot.GetLineTracker().SetRoute(LineTracker::Straight);
		break;
	case Left:
		robot.GetLineTracker().SetRoute(LineTracker::ForkLeft);
		break;
	case Right:
		robot.GetLineTracker().SetRoute(LineTracker::ForkRight);
		break;
	case Smart:
		robot.GetLineTracker().SetRoute(LineTracker::Straight);
		break;
	}
	robot.GetManip().TryReset();
	robot.GetManip().SetClose(true);
	timer.Start();
	orient.Enable();
}

ForkAuto::~ForkAuto() { }

void ForkAuto::Periodic()
{
	switch (state)
	{
	case TrackingLine:
		if (robot.GetLineTracker().IsAtEnd() && timer.Get() > 9.0)
		{
			state = PlacingTube;
			timer.Reset();
		}
		
		if (timer.Get() > 11.0)
			state = Finished;
		
		if (isSmart && SMART_START_TIME < timer.Get() && timer.Get() < SMART_END_TIME)
		{
			// Check the furthest ultrasonic sensor here, and switch drive mode
			float left = robot.GetLeftUltrasound().GetVoltage();
			float right = robot.GetRightUltrasound().GetVoltage();
			if (left >= right)
				robot.GetLineTracker().SetRoute(LineTracker::ForkLeft);
			else if (right > left)
				robot.GetLineTracker().SetRoute(LineTracker::ForkRight);
		}
		
		robot.GetManip().SetLowPeg();
		robot.GetDrive().MecanumDrive_Cartesian(
				robot.GetLineTracker().GetDriveStrafe(),
				((0.1f - SPEED_MULTIPLIER) / 10) * timer.Get() + SPEED_MULTIPLIER,
				orient.GetDriveRotation());
		break;
		
	case PlacingTube:
		if (timer.Get() > 1.0)
		{
			state = MovingToCenter;
			timer.Reset();
		}
		
		robot.GetDrive().HolonomicDrive(0, 0, 0);
		robot.GetManip().SetOpen();
		robot.GetManip().SetManual(0);
		break;
		
	case MovingToCenter:
		if (timer.Get() > 3.0)
			state = Finished;
		
		robot.GetDrive().HolonomicDrive(0.3f, 0, orient.GetDriveRotation());
		break;
		
	case Finished:
		robot.GetDrive().HolonomicDrive(0, 0, 0);
	}
}
