#ifndef ROBOTHARDWARE_H
#define ROBOTHARDWARE_H

#include "WPILib.h"
#include "LineTracker.h"
#include "ObjectManip.h"

class RobotHardware
{
public:
	RobotHardware();
	
	Jaguar& GetLeftFrontJaguar();
	Jaguar& GetRightFrontJaguar();
	Jaguar& GetLeftRearJaguar();
	Jaguar& GetRightRearJaguar();
	RobotDrive& GetDrive();
	LineTracker& GetLineTracker();
	ObjectManip& GetManip();
	Gyro& GetGyro();
	AnalogChannel& GetFrontUltrasound();
	AnalogChannel& GetRearUltrasound();
	AnalogChannel& GetLeftUltrasound();
	AnalogChannel& GetRightUltrasound();
	
private:
	Jaguar leftFrontJaguar, rightFrontJaguar, leftRearJaguar, rightRearJaguar;
	RobotDrive drive;
	LineTracker lineTracker;
	ObjectManip manip;
	Gyro gyro;
	AnalogChannel frontUltrasound, rearUltrasound, leftUltrasound, rightUltrasound;
	Compressor compressor;
};

#endif
