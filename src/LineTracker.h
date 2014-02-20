#ifndef LINETRACKER_H
#define LINETRACKER_H

#include "WPILib.h"

class LineTracker
{
public:
	enum RouteType
	{
		Straight,
		ForkLeft,
		ForkRight
	};
	
	LineTracker(UINT32 leftChannel, UINT32 middleChannel, UINT32 rightChannel);
	float GetDriveStrafe();
	RouteType GetRoute();
	void SetRoute(RouteType type);
	bool GetLeftSensor();
	bool GetMiddleSensor();
	bool GetRightSensor();
	bool IsAtEnd();
	
private:
	float DriveStrafeFromPrevious();
	
	DigitalInput left, middle, right;
	RouteType currentRoute;
	float defaultStrafe;
	int previousValue;
};

#endif
