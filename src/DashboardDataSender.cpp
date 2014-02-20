#include "DashboardDataSender.h"

DashboardDataSender::DashboardDataSender(RobotHardware& robot) :
	robot(robot)
{ }

void DashboardDataSender::SendDashboardData() {
	Dashboard &dash = DriverStation::GetInstance()->GetLowPriorityDashboardPacker();
	dash.AddCluster();
	{
		dash.AddCluster();
		{ //analog modules 
			dash.AddCluster();
			{
				float angle = fmod(robot.GetGyro().GetAngle(), 360.0f);
				if (angle < 0) angle += 360;
				
				dash.AddFloat(angle);
				dash.AddFloat((float) robot.GetManip().GetEncoder());
				dash.AddFloat((int)(robot.GetFrontUltrasound().GetAverageVoltage()*(1000.0/3.0625)/2.54)); // place for front ultrasound
				dash.AddFloat((int)(robot.GetRearUltrasound().GetAverageVoltage()*(1000.0/3.0625)/2.54)); // place for rear ultrasound
				
				for (int i = 1; i <= 4; i++) {
					dash.AddFloat((float) 0.0);
				}
			}
			dash.FinalizeCluster();
			dash.AddCluster();
			{
				for (int i = 1; i <= 8; i++) {
					dash.AddFloat((float) 0.0);
				}
			}
			dash.FinalizeCluster();
		}
		dash.FinalizeCluster();

		dash.AddCluster();
		{ //digital modules
			dash.AddCluster();
			{
				dash.AddCluster();
				{
					int module = 4;
					dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward());
					dash.AddU8(DigitalModule::GetInstance(module)->GetRelayReverse());
					
					
					UINT16 bit1 = DigitalModule::GetInstance(module)->GetDIO(1);
					UINT16 bit2 = DigitalModule::GetInstance(module)->GetDIO(3);
					UINT16 result = (bit1) | (bit2 << 1);
					
					dash.AddU16(result);
						
					//dash.AddU16((short)DigitalModule::GetInstance(module)->GetDIO());
					dash.AddU16((short)DigitalModule::GetInstance(module)->GetDIODirection());
					dash.AddCluster();
					{
						for (int i = 1; i <= 16; i++) {
							dash.AddU8((unsigned char) 0);
						}
					}
					dash.FinalizeCluster();
				}
				dash.FinalizeCluster();
			}
			dash.FinalizeCluster();

			dash.AddCluster();
			{
				dash.AddCluster();
				{
					int module = 6;
					dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward());
					dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward());
					dash.AddU16((short)DigitalModule::GetInstance(module)->GetDIO());
					dash.AddU16(DigitalModule::GetInstance(module)->GetDIODirection());
					dash.AddCluster();
					{
						for (int i = 1; i <= 10; i++) {
							dash.AddU8((unsigned char)0);
						}
					}
					dash.FinalizeCluster();
				}
				dash.FinalizeCluster();
			}
			dash.FinalizeCluster();
		}
		dash.FinalizeCluster();

		// Can't read solenoids without an instance of the object
		dash.AddU8((char) 0);
	}
	dash.FinalizeCluster();
	dash.Finalize();
}
