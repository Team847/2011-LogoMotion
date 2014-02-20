#include "LineTracker.h"

LineTracker::LineTracker(UINT32 leftChannel, UINT32 middleChannel, UINT32 rightChannel) :
	left(leftChannel),
	middle(middleChannel),
	right(rightChannel),
	currentRoute(Straight),
	defaultStrafe(0.5f),
	previousValue(0)
{ }

float LineTracker::GetDriveStrafe()
{	
	if (IsAtEnd())
		return 0;
	
	float strafe = 0;
	int binaryValue = 4 * GetLeftSensor() + 2 * GetMiddleSensor() + GetRightSensor();
	
	switch (currentRoute)
	{
	case Straight:
		if (binaryValue == 0)
			strafe = DriveStrafeFromPrevious();
		else if (binaryValue == 1 || binaryValue == 3)
			strafe = defaultStrafe;
		else if (binaryValue == 2 || binaryValue == 5)
			strafe = 0;
		else if (binaryValue == 4 || binaryValue == 6)
			strafe = -defaultStrafe;
		break;
	case ForkRight:
		if (binaryValue == 0)
			strafe = DriveStrafeFromPrevious();
		else if (binaryValue == 1)
			strafe = 0;
		else if (2 <= binaryValue && binaryValue <= 6)
			strafe = -defaultStrafe;
		break;
	case ForkLeft:
		if (binaryValue == 0)
			strafe = DriveStrafeFromPrevious();
		else if (binaryValue == 4)
			strafe = 0;
		else if ((1 <= binaryValue && binaryValue <= 3) || binaryValue == 5 || binaryValue == 6)
			strafe = defaultStrafe;
		break;
	}
	
	if (binaryValue != 0)
		previousValue = binaryValue;
	
	return strafe;
}

LineTracker::RouteType LineTracker::GetRoute()
{
	return currentRoute;
}

void LineTracker::SetRoute(RouteType route)
{
	currentRoute = route;
}

bool LineTracker::GetLeftSensor()
{
	return !left.Get();
}

bool LineTracker::GetMiddleSensor()
{
	return !middle.Get();
}

bool LineTracker::GetRightSensor()
{
	return !right.Get();
}

bool LineTracker::IsAtEnd()
{
	return GetLeftSensor() && GetMiddleSensor() && GetRightSensor();
}

float LineTracker::DriveStrafeFromPrevious()
{
	if (previousValue == 4 || previousValue == 6)
		return -defaultStrafe;
	else
		return defaultStrafe;
}
