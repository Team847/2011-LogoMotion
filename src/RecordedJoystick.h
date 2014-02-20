#ifndef HAVE_RECORDED_JOYSTICK_H
#define HAVE_RECORDED_JOYSTICK_H

#include "WPILib.h"

#include <fstream>

class RecordedJoystick : public GenericHID
{
public:
	RecordedJoystick(const char* filename);
	~RecordedJoystick();
	
	void Start();
	void Stop();
	void Reset();
	
	virtual float GetX(JoystickHand hand = kRightHand);
	virtual float GetY(JoystickHand hand = kRightHand);
	virtual float GetZ();
	virtual float GetTwist();
	virtual float GetThrottle();
	virtual float GetRawAxis(UINT32 axis);

	virtual bool GetTrigger(JoystickHand hand = kRightHand);
	virtual bool GetTop(JoystickHand hand = kRightHand);
	virtual bool GetBumper(JoystickHand hand = kRightHand);
	virtual bool GetRawButton(UINT32 button);
	
private:
	// Default values for the convience functions
	static const UINT32 defaultXAxis = 0;
	static const UINT32 defaultYAxis = 1;
	static const UINT32 defaultZAxis = 2;
	static const UINT32 defaultTwistAxis = 3;
	static const UINT32 defaultThrottleAxis = 2;
	
	static const UINT32 defaultTriggerButton = 0;
	static const UINT32 defaultTopButton = 1;
	
	vector<vector<float> > axes;
	vector<vector<bool> > buttons;
	
	Timer timer;
	float recordingInterval;
	UINT32 NearestRecording();
	
	void ParseFile(const char* filename);
};

#endif
