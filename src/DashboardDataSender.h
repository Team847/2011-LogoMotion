#ifndef DASHBOARDDATASENDER_H
#define DASHBOARDDATASENDER_H

#include "RobotHardware.h"
#include <math.h>

class DashboardDataSender
{
public:
	DashboardDataSender(RobotHardware& robot);
	void SendDashboardData();
	
private:
	RobotHardware& robot;
};

#endif
