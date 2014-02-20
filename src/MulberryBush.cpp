#include "MulberryBush.h"

MulberryBush::MulberryBush(Jaguar* lfjag, Jaguar* rfjag, Jaguar* lrjag, Jaguar* rrjag){
	rearultrasound = new AnalogChannel(3);
	leftfrontjag = lfjag; // adding the jaguar and the wheels to control them seperatly
	rightfrontjag = rfjag;
	leftrearjag = lrjag;
	rightrearjag = rrjag;
	
}

MulberryBush::~MulberryBush(){
	delete rearultrasound;
}
void MulberryBush::DriveMulberry(float twistvalue){
	float ultrasoundvoltage = rearultrasound->GetVoltage();
	float distance = ultrasoundvoltage*(1000.0/4.9)/2.54; // Using the ratio the ultra sound uses and convert the number to inches
	float rmult = (ROBOTLENGTH+15+distance)/(15+distance); // Adding distances together to find speeds of seperate wheel axis
	if (distance < 10.0 || (twistvalue < 0.1 && twistvalue > -0.1))
	{
		leftfrontjag->Set(0.0);
		rightfrontjag->Set(0.0);
		leftrearjag->Set(0.0);
		rightrearjag->Set(0.0);
	};
	if (twistvalue > 0.1)
	{ 
		leftfrontjag->Set(LOWSPEED);
		rightfrontjag->Set(HIGHSPEED);
		leftrearjag->Set(rmult*HIGHSPEED);
		rightrearjag->Set(rmult*LOWSPEED);
	
}
	if (twistvalue < -0.1)
	{
		leftfrontjag->Set(HIGHSPEED);
		rightfrontjag->Set(LOWSPEED);
		leftrearjag->Set(rmult*LOWSPEED);
		rightrearjag->Set(rmult*HIGHSPEED);
	}	
	
}
