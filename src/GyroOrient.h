#ifndef GYROORIENT_H
#define GYROORIENT_H

#include "WPILib.h"
#include <math.h>

class GyroOrient : public PIDOutput, public PIDSource
{
public:
	GyroOrient(Gyro& gyro);
	virtual ~GyroOrient();
	void PIDWrite(float output);
	double PIDGet();
	void Enable();
	bool IsEnabled();
	void Reset();
	float GetDriveRotation();
	
private:
	PIDController pid;
	Gyro& gyro;
	float rotation;
};

#endif
