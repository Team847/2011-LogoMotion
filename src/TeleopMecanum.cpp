#include "TeleopMecanum.h"

TeleopMecanum::TeleopMecanum (RobotHardware& robot, DriverHardware& driver) :
	TeleopMode(robot, driver),
	autodrive (14),
	FinishAuto(autodrive.Get()),
	Xzero (true),
	Yzero (true),
	Zzero (true),
	timer(),
	orient(robot.GetGyro()),
	bush(&robot.GetLeftFrontJaguar(), &robot.GetRightFrontJaguar(), &robot.GetRightRearJaguar(), &robot.GetLeftRearJaguar())
{
	timer.Start();
	robot.GetManip().TryReset();
}

TeleopMecanum::~TeleopMecanum()
{ }

void TeleopMecanum::Periodic()
{
	GenericHID& stick = driver.GetRightJoystick();
	GenericHID& stick2 = driver.GetLeftJoystick();
	//printf("Y %f, X %f, Z%f\n", Magnitude(stick), stick.GetX(), stick.GetZ());
	if (!FinishAuto)
	{
		robot.GetDrive().MecanumDrive_Polar(-0.5, 180.0, 0.0);
		
		if (Magnitude(stick) < -0.05 || Magnitude(stick) > 0.05)
			Yzero = false;
		if (stick.GetX() < -0.05 || stick.GetX() > 0.05)
			Xzero = false;
		if (stick.GetZ() < -0.05 || stick.GetZ() > 0.05)
			Zzero = false;
		
		if (!Xzero || !Yzero || !Zzero || timer.Get() > 1.0)
			FinishAuto = true;
	}
	else
	{
		if (orient.IsEnabled())
			robot.GetDrive().HolonomicDrive(-0.75f * Magnitude(stick), Direction(stick), orient.GetDriveRotation());
		else if (stick.GetRawButton(DRIVEBUSHBUTTON))
			bush.DriveMulberry(stick.GetZ());
		else
			robot.GetDrive().HolonomicDrive(-0.75f * Magnitude(stick), Direction(stick), -0.7f * TwistReduce(stick.GetZ()));
		
		if (!(stick2.GetRawButton(MANIPFLOORBUTTON) || stick2.GetRawButton(MANIPLOWBUTTON) || stick2.GetRawButton(MANIPHIGHBUTTON) || stick2.GetRawButton(MANIPSLOTBUTTON) || stick2.GetRawButton(MANIPCARRYBUTTON)))
			robot.GetManip().SetManual(stick2.GetY());
		else if (stick2.GetRawButton(MANIPFLOORBUTTON))
			robot.GetManip().SetFloor();
		else if (stick2.GetRawButton(MANIPLOWBUTTON))
			robot.GetManip().SetLowPeg();
		else if (stick2.GetRawButton(MANIPHIGHBUTTON))
			robot.GetManip().SetHighPeg();
		else if (stick2.GetRawButton(MANIPSLOTBUTTON))
			robot.GetManip().SetSlot();
		else if (stick2.GetRawButton(MANIPCARRYBUTTON))
			robot.GetManip().SetCarry();
		
		if (stick2.GetRawButton(MANIPRESET))
			robot.GetManip().TryReset();
		
		if (stick.GetRawButton(DRIVEGYROBUTTON))
			orient.Enable();
		else
			orient.Reset();
		
		//printf("Drive Throttle Value %f\n", stick.GetRawAxis(4));
		
		if (stick.GetTrigger() || stick2.GetTrigger())
			robot.GetManip().SetOpen();
		else
			robot.GetManip().SetClose(true);
		
		if (stick2.GetRawButton(MANIPMINIDEPLOY))
			robot.GetManip().DeployMini();
		else if (MiniDeploy && !stick2.GetRawButton(MANIPMINIDEPLOY))
			robot.GetManip().RetractMini();
		
		MiniDeploy = stick2.GetRawButton(MANIPMINIDEPLOY);
		DriveTrigger = stick.GetRawButton(DRIVECLAW);
		ManipTrigger = stick2.GetRawButton(MANIPCLAW);
	}
}

float TeleopMecanum::TwistReduce(float input)
{
	return .625*(fabs(input+.2)+fabs(input-.2)-.4)*2.5*(fabs(input+.2)-fabs(input-.2));
}

float TeleopMecanum::Magnitude(GenericHID& joystick)
{
	return sqrt(joystick.GetX() * joystick.GetX() + joystick.GetY() * joystick.GetY());
}

float TeleopMecanum::Direction(GenericHID& joystick)
{
	return atan2(joystick.GetY(), joystick.GetX()) * 180 / 3.1416 + 90;
}
