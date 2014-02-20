#include "TeleopMode.h"

TeleopMode::TeleopMode(RobotHardware& robot, DriverHardware& driver) :
	robot(robot),
	driver(driver)
{ }

void TeleopMode::Periodic()
{ }

void TeleopMode::Continuous()
{ }
