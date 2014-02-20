#include "AutonomousReset.h"

AutonomousReset::AutonomousReset(RobotHardware& robot) :
	AutonomousMode(robot)
{ }

void AutonomousReset::Periodic()
{
	robot.GetDrive().HolonomicDrive(0, 0, 0);
	robot.GetManip().SetManual(0.7f);
	robot.GetManip().TryReset();
	robot.GetManip().SetOpen();
	robot.GetGyro().Reset();
}
