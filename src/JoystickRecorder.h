#ifndef HAVE_JOYSTICK_RECORDER_H
#define HAVE_JOYSTICK_RECORDER_H

#include "WPILib.h"

#include <fstream>

class JoystickRecorder
{
public:
	JoystickRecorder(GenericHID* joystick);
	~JoystickRecorder();
	
	void Start(char* filename, float recordingInterval, int numberOfAxes, int numberOfButtons);
	void Stop();
	
private:
	GenericHID* joystick;
	ofstream* file;
	
	Task task;
	static void WriteData(ofstream* file, GenericHID* joystick, int millisecondInterval, int numberOfAxes, int numberOfButtons);
};

#endif
