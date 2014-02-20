#include "PHREDRobot.h"

void PHREDRobot::RobotInit()
{
	robotHardware = new RobotHardware();
	realDriverHardware = NULL;
	virtualDriverHardware = NULL;
	autonomous = NULL;
	teleop = NULL;
	leftRecorder = NULL;
	rightRecorder = NULL;
	dash = new DashboardDataSender(*robotHardware);
	isLearnMode = false;
}

void PHREDRobot::AutonomousInit()
{
	if (leftRecorder != NULL)
		leftRecorder->Stop();
	if (rightRecorder != NULL)
		rightRecorder->Stop();
	
	isLearnMode = false;
	robotHardware->GetDrive().SetSafetyEnabled(false);
	delete autonomous;
	
	DriverStation* driverStation = DriverStation::GetInstance();
	if (driverStation->GetDigitalIn(1))
		autonomous = new AutonomousReset(*robotHardware);
	else if (driverStation->GetDigitalIn(2))
		autonomous = new LinetrackAuto(*robotHardware);
	else if (driverStation->GetDigitalIn(3))
		autonomous = new ForkAuto(*robotHardware, ForkAuto::Left);
	else if (driverStation->GetDigitalIn(4))
		autonomous = new ForkAuto(*robotHardware, ForkAuto::Right);
	else if (driverStation->GetDigitalIn(5))
		autonomous = new ForkAuto(*robotHardware, ForkAuto::Smart);
	else
	{
		int learnMode = ((int)driverStation->GetDigitalIn(6)) << 1 | ((int)driverStation->GetDigitalIn(7));
		
		if (learnMode == 0)
			autonomous = new BasicAuto(*robotHardware);
		else
		{
			char filename1[15];
			char filename2[15];
			sprintf(filename1, "Learn%d-1.txt", learnMode);
			sprintf(filename2, "Learn%d-2.txt", learnMode);
			
			delete virtualDriverHardware;
			virtualDriverHardware = new VirtualDriverHardware(filename1, filename2);
			
			delete teleop;
			teleop = new TeleopMecanum(*robotHardware, *virtualDriverHardware);
			
			virtualDriverHardware->Start();
			isLearnMode = true;
		}
	}
}

void PHREDRobot::AutonomousPeriodic()
{
	dash->SendDashboardData();
	LineTracker& track = robotHardware->GetLineTracker();
	printf("L %d M %d R %d\n", track.GetLeftSensor(), track.GetMiddleSensor(), track.GetRightSensor());
	
	if (!isLearnMode)
		autonomous->Periodic();
	else
		teleop->Periodic();
}

void PHREDRobot::AutonomousContinuous()
{
	if (!isLearnMode)
		autonomous->Continuous();
	else
		teleop->Continuous();
}

void PHREDRobot::TeleopInit()
{
	if (realDriverHardware == NULL)
		realDriverHardware = new RealDriverHardware();
	
	if (leftRecorder == NULL)
		leftRecorder = new JoystickRecorder(&realDriverHardware->GetLeftJoystick());
	if (rightRecorder == NULL)
		rightRecorder = new JoystickRecorder(&realDriverHardware->GetRightJoystick());
	
	DriverStation* driverStation = DriverStation::GetInstance();
	if (driverStation->GetDigitalIn(8))
	{
		int learnMode = ((int)driverStation->GetDigitalIn(6)) << 1 | ((int)driverStation->GetDigitalIn(7));
		
		if (learnMode != 0)
		{
			char filename1[15];
			char filename2[15];
			sprintf(filename1, "Learn%d-1.txt", learnMode);
			sprintf(filename2, "Learn%d-2.txt", learnMode);
			
			leftRecorder->Start(filename1, 0.05f, 2, 8);
			rightRecorder->Start(filename2, 0.05f, 3, 3);
		}
	}
	
	robotHardware->GetDrive().SetSafetyEnabled(false);
	delete teleop;
	
	teleop = new TeleopMecanum(*robotHardware, *realDriverHardware);
}

void PHREDRobot::TeleopPeriodic()
{
	dash->SendDashboardData();
	teleop->Periodic();
}

void PHREDRobot::TeleopContinuous()
{
	teleop->Continuous();
}

void PHREDRobot::DisabledInit()
{
	if (leftRecorder != NULL)
		leftRecorder->Stop();
	if (rightRecorder != NULL)
		rightRecorder->Stop();
}

void PHREDRobot::DisabledPeriodic()
{
	dash->SendDashboardData();
}

void PHREDRobot::DisabledContinuous()
{ }
