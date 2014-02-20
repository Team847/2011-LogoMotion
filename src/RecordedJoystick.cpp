#include "RecordedJoystick.h"

RecordedJoystick::RecordedJoystick(const char* filename):
	axes(),
	buttons(),
	timer(),
	recordingInterval(0.0f)
{
	ParseFile(filename);
}

RecordedJoystick::~RecordedJoystick()
{
	// Nothing to do here
}

void RecordedJoystick::Start()
{
	timer.Start();
}

void RecordedJoystick::Stop()
{
	timer.Stop();
}

void RecordedJoystick::Reset()
{
	timer.Reset();
}

float RecordedJoystick::GetX(JoystickHand hand)
{
	return axes[NearestRecording()][defaultXAxis];
}

float RecordedJoystick::GetY(JoystickHand hand)
{
	return axes[NearestRecording()][defaultYAxis];
}

float RecordedJoystick::GetZ()
{
	return axes[NearestRecording()][defaultZAxis];
}

float RecordedJoystick::GetTwist()
{
	return axes[NearestRecording()][defaultTwistAxis];
}

float RecordedJoystick::GetThrottle()
{
	return axes[NearestRecording()][defaultTwistAxis];
}

float RecordedJoystick::GetRawAxis(UINT32 axis)
{
	return axes[NearestRecording()][axis - 1];
}

bool RecordedJoystick::GetTrigger(JoystickHand hand)
{
	return buttons[NearestRecording()][defaultTriggerButton];
}

bool RecordedJoystick::GetTop(JoystickHand hand)
{
	return buttons[NearestRecording()][defaultTopButton];
}

bool RecordedJoystick::GetBumper(JoystickHand hand)
{
	return false;
}

bool RecordedJoystick::GetRawButton(UINT32 button)
{
	return buttons[NearestRecording()][button - 1];
}

UINT32 RecordedJoystick::NearestRecording()
{
	UINT32 index = (UINT32)(timer.Get() / recordingInterval);
	if (index >= axes.size() || index >= buttons.size())
		return axes.size() - 1;
	else
		return index;
}

void RecordedJoystick::ParseFile(const char* filename)
{
	ifstream file(filename);
	
	if (!file.is_open())
	{
		cerr << "RecordedJoystick file \"" << filename << "\" could not be opened.";
		recordingInterval = 1;
		axes.push_back(vector<float>(4,0));
		buttons.push_back(vector<bool>(15,false));
		return;
	}
	
	string str;
	int numberOfAxes = 0;
	int numberOfButtons = 0;
	
	// Get header information (interval, axes, buttons)
	getline(file, str, '~');
	sscanf(str.c_str(), " interval: %f axes: %d buttons: %d", &recordingInterval, &numberOfAxes, &numberOfButtons);
	
	while (!file.eof() && file.peek() != 'x')
	{
		vector<float> currentAxes;
		for (int i = 0; i < numberOfAxes; i++)
		{
			getline(file, str, ',');
			currentAxes.push_back(atof(str.c_str()));
		}
		
		vector<bool> currentButtons;
		for (int i = 0; i < numberOfButtons; i++)
		{
			getline(file, str, ',');
			if (str == "T") currentButtons.push_back(true);
			else currentButtons.push_back(false);
		}
		
		axes.push_back(currentAxes);
		buttons.push_back(currentButtons);
	}
	
	file.close();
}
