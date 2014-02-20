#ifndef PHREDROBOT_H
#define PHREDROBOT_H

#include "WPILib.h"
#include "RobotHardware.h"
#include "RealDriverHardware.h"
#include "VirtualDriverHardware.h"
#include "AutonomousMode.h"
#include "TeleopMode.h"
#include "TeleopMecanum.h"
#include "DashboardDataSender.h"
#include "BasicAuto.h"
#include "LinetrackAuto.h"
#include "ForkAuto.h"
#include "AutonomousReset.h"
#include "JoystickRecorder.h"

class PHREDRobot : public IterativeRobot
{
public:
	virtual void RobotInit();
	
	virtual void DisabledInit();
	virtual void AutonomousInit();
	virtual void TeleopInit();
	
	virtual void DisabledPeriodic();
	virtual void AutonomousPeriodic();
	virtual void TeleopPeriodic();
	
	virtual void DisabledContinuous();
	virtual void AutonomousContinuous();
	virtual void TeleopContinuous();
	
private:
	RobotHardware* robotHardware;
	RealDriverHardware* realDriverHardware;
	VirtualDriverHardware* virtualDriverHardware;
	AutonomousMode* autonomous;
	TeleopMode* teleop;
	DashboardDataSender* dash;
	bool isLearnMode;
	JoystickRecorder* leftRecorder;
	JoystickRecorder* rightRecorder;
};

START_ROBOT_CLASS(PHREDRobot);

#endif
