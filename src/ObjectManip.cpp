#include "ObjectManip.h"

ObjectManip::ObjectManip() {
	armloader = new Victor(ARML);
	claw = new DoubleSolenoid(CLAW1, CLAW2);
    miniclaw = new DoubleSolenoid(CLAW3, CLAW4);
	tubelimitswitch = new DigitalInput(TLS);
	backlimitswitch = new DigitalInput(BLS);
	frontlimitswitch = new DigitalInput(FLS);
	encoderarm = new Encoder(ENCA,ENCB);
	
	encoderarm->Start();
}
ObjectManip::~ObjectManip() {
	delete armloader;
	delete claw;
	delete miniclaw;
	delete tubelimitswitch;
	delete encoderarm;

}//arm picks up tubes from floor
void ObjectManip::SetFloor() {
	int armcountfloor = encoderarm->Get();
	float armdegreesfloor = (armcountfloor*(360.0/ENCOUNT));
	float speed = Armspeed(armdegreesfloor, SETF);
	if (frontlimitswitch->Get())
		armloader->Set(0.0f);
	else	
		armloader->Set(speed);
}//carrying tubes
void ObjectManip::SetCarry() {
	int armcountcarry = encoderarm->Get();
	float armdegreescarry = (armcountcarry*(360.0/ENCOUNT));
	float speed = Armspeed(armdegreescarry, SETC);
	if (speed>1)speed = 1;
	if (backlimitswitch->Get())
		armloader->Set(0.0f);
	else
		armloader->Set(speed);
    
}//set tube on low peg
void ObjectManip::SetLowPeg() {
	int armcountlow = encoderarm->Get();
	float armdegreeslow = (armcountlow*(360.0/ENCOUNT));
	float speed = Armspeed(armdegreeslow, SETL);
	armloader->Set(speed);
			
}//set tube on medium peg
void ObjectManip::SetHighPeg() {
	int armcounthigh = encoderarm->Get();
	int armdegreeshigh = (int)(armcounthigh*(360.0/ENCOUNT));
	float speed = Armspeed(armdegreeshigh, SETH);
	armloader->Set(speed);

}//grab tube from slot
void ObjectManip::SetSlot() {
	int armcountslot = encoderarm->Get();
	float armdegreesslot = (armcountslot*(360.0/ENCOUNT));
	float speed = Armspeed(armdegreesslot, SETS);
	armloader->Set(speed);

} //preset for simple transportation of tubes	
void ObjectManip::SetTransport() {
	int armcounttrans = encoderarm->Get();
	float armdegreestrans = (armcounttrans*(360.0/ENCOUNT));
	float speed = Armspeed(armdegreestrans, TRANS);
	armloader->Set(speed);
	
}//claw opens
void ObjectManip::SetOpen(){
	claw->Set (DoubleSolenoid::kForward);
}
void ObjectManip::DeployMini(){
	miniclaw->Set(DoubleSolenoid::kForward);
	
}
void ObjectManip::RetractMini(){
	miniclaw->Set(DoubleSolenoid::kReverse);
}
/*claw closes 
 * clawOverride= true then limit switch is inaccesible and claw closes
 * if false then claw is open and limit switch is useable
 */
void ObjectManip::SetClose(bool clawOverride) {
	if(tubelimitswitch->Get()||clawOverride)claw->Set (DoubleSolenoid::kReverse); 
}//manual driver takeover
void ObjectManip::SetManual(float stickvalue) {
	stickvalue *= 0.7f;
	//determines switch default state
	if (frontlimitswitch->Get() && -stickvalue > 0)
		armloader->Set(0.0);
	else if (frontlimitswitch->Get() && -stickvalue < 0)
		armloader->Set(stickvalue);
	else if (backlimitswitch->Get() && -stickvalue < 0)
		armloader->Set(0.0);
	else if (backlimitswitch->Get() && -stickvalue > 0)
		armloader->Set(stickvalue);
	else
		armloader->Set(stickvalue);
}//checks limit switch and reset if pressed
void ObjectManip::TryReset() {
	if (backlimitswitch->Get()) encoderarm->Reset(); //true means switch is closed
}	
	
float ObjectManip::GetEncoder(){
	int armcount = encoderarm->Get();
	float armdegrees = armcount*(360.0/ENCOUNT);
	return armdegrees;	
}//checks to see if encoder value is ridiculous

bool ObjectManip::OutOfRange(){
	int armcount = encoderarm->Get();
	float armdegrees = armcount*(360.0/ENCOUNT);
	if (armdegrees > 49 && armdegrees < SETF) return true;
	else return false;
}

float ObjectManip::Armspeed(float position, float target)
{
	float lowTarget = target - 2;
	float highTarget = target + 2;
	float speed;
	
	if (position < lowTarget)
		speed = CalculateSlope(0, 0.6f, target, 0.4f) * position + 0.6f;
	else if (position > highTarget)
	{
		float slope = CalculateSlope(target, -0.4f, SETF, -0.6f);
		float intercept = -0.6f - slope * SETF;
		speed = slope * position + intercept;
	}
	else
		speed = 0;
	
	return -speed;
}

float ObjectManip::CalculateSlope(float x1, float y1, float x2, float y2)
{
	return (y2 - y1) / (x2 - x1);
}

