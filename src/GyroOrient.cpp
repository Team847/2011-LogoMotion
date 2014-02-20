#include "GyroOrient.h"

GyroOrient::GyroOrient(Gyro& gyro) :
	pid(0, 0, 0, this, this),
	gyro(gyro),
	rotation(0)
{
	pid.SetInputRange(0, 360);
	pid.SetContinuous();
	pid.SetOutputRange(-1, 1);
	pid.SetSetpoint(0);
	pid.SetTolerance(2);
	pid.SetPID(0.01f, 0, 0);
}

GyroOrient::~GyroOrient()
{ }

void GyroOrient::PIDWrite(float output)
{
	rotation = -output;
}

double GyroOrient::PIDGet()
{
	float angle = fmod(gyro.GetAngle(), 360.0f);
	if (angle < 0) angle += 360;
	return angle;
}

void GyroOrient::Enable()
{
	if (!IsEnabled())
	{
		pid.SetSetpoint(gyro.GetAngle());
		pid.Enable();
	}
}

bool GyroOrient::IsEnabled()
{
	return pid.IsEnabled();
}

void GyroOrient::Reset()
{
	pid.Reset();
}

float GyroOrient::GetDriveRotation()
{
	return rotation;
}
