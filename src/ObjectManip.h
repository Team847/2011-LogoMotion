#ifndef OBJECTMANIP_H
#define OBJECTMANIP_H

#define ARML 5 //armloader values
#define CLAW1 1 //claw values
#define CLAW2 2 //claw 2 values
#define CLAW3 3 //mini bot deployer
#define CLAW4 4 //mini boy deployer
#define TLS 2 //tubelimitswitch values
#define BLS 1 //backlimitswitch values
#define FLS 3 //frontlimitswitch values
#define ENCA 7 //encoder channel 1 values
#define ENCB 8 //encoder channel 2 values

#define HALFSP 0.5 //half speed of victor motor
#define STOP 0.0 //stops victor motor
#define BHS -0.5 //backwards at half speed of victor motor


#define ENCOUNT 300.0 //encoder count

#define SETC 0
#define SETL 22
#define SETH 0
#define SETF 90
#define SETS 20
#define TRANS 60

#include "WPILib.h"
class ObjectManip{
public:
	ObjectManip();   //constructor
	~ObjectManip();  //destructor
	
	
	void SetFloor();  //arm to floor level
	void SetCarry();  //carrying tubes
	void SetLowPeg();  //place on low peg
	void SetHighPeg();  //place on high peg
	void SetSlot();  //take from slot
	void SetTransport(); //preset for simple transportation of tubes
	void SetOpen();  //claw opening
	void SetClose(bool clawOverride);  //claw closing
	void SetManual(float stickvalue);  //manual arm control
	void TryReset(); //checks limit switch and reset if pressed
	void DeployMini(); //deploys mini bot
	void RetractMini(); //minibot come home!
	bool OutOfRange(); //checks if encoder value is ridiculous
	float GetEncoder(); // takes reading, changes to degrees  returns value
	
private: 
	Victor * armloader;  //motor that controls arm lift
	DoubleSolenoid * claw;  //controls/powers opening and closing of claw
	DoubleSolenoid * claw2; //controls powers opening and closing of claw 2
	DoubleSolenoid * miniclaw; //deploys mini bot
	DigitalInput * tubelimitswitch; //limit switch
	DigitalInput * frontlimitswitch; //front limit switch 
	DigitalInput * backlimitswitch; //protects from destroying robot and tells encoder when to zero self
	Encoder * encoderarm; //determines speed and position of arm
	float Armspeed(float position, float target);//function that determines arm speed
	float CalculateSlope(float x1, float y1, float x2, float y2); // fuction that calculates slope
};
#endif

