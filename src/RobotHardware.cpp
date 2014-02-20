#include "RobotHardware.h"

RobotHardware::RobotHardware() :
	leftFrontJaguar(1),
	rightFrontJaguar(2),
	leftRearJaguar(3),
	rightRearJaguar(4),
	drive(&leftFrontJaguar, &leftRearJaguar, &rightFrontJaguar, &rightRearJaguar),
	lineTracker(12, 11, 10),
	manip(),
	gyro(1),
	frontUltrasound(3),
	rearUltrasound(5),
	leftUltrasound(2),
	rightUltrasound(4),
	compressor(13, 1)
{
	compressor.Start();
	drive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	drive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	AxisCamera::GetInstance();
}

Jaguar& RobotHardware::GetLeftFrontJaguar()
{
	return leftFrontJaguar;
}

Jaguar& RobotHardware::GetRightFrontJaguar()
{
	return rightFrontJaguar;
}

Jaguar& RobotHardware::GetLeftRearJaguar()
{
	return leftRearJaguar;
}

Jaguar& RobotHardware::GetRightRearJaguar()
{
	return rightRearJaguar;
}

RobotDrive& RobotHardware::GetDrive()
{
	return drive;
}

LineTracker& RobotHardware::GetLineTracker()
{
	return lineTracker;
}

ObjectManip& RobotHardware::GetManip()
{
	return manip;
}

Gyro& RobotHardware::GetGyro()
{
	return gyro;
}

AnalogChannel& RobotHardware::GetFrontUltrasound()
{
	return frontUltrasound;
}

AnalogChannel& RobotHardware::GetRearUltrasound()
{
	return rearUltrasound;
}

AnalogChannel& RobotHardware::GetLeftUltrasound()
{
	return leftUltrasound;
}

AnalogChannel& RobotHardware::GetRightUltrasound()
{
	return rightUltrasound;
}
