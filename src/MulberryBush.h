#ifndef MULBERRYBUSH_H
#define MULBERRYBUSH_H
#define HIGHSPEED 0.5
#define LOWSPEED -0.5
#define ROBOTLENGTH 24.5
#include "WPILib.h"
class MulberryBush{

public:
	MulberryBush(Jaguar* lfjag, Jaguar* rfjag, Jaguar* lrjag, Jaguar* rrjag);   //constructor
	~MulberryBush();  //destructor
	void DriveMulberry(float twistvalue); // Activates Drive
	
	
private: 
	AnalogChannel * rearultrasound; // Measures Distance to the Minibot platform
	Jaguar* leftfrontjag;
	Jaguar* rightfrontjag;
	Jaguar* leftrearjag;
	Jaguar* rightrearjag;

};
#endif
