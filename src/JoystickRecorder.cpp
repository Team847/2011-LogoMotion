#include "JoystickRecorder.h"

JoystickRecorder::JoystickRecorder(GenericHID* joystick) :
	joystick(joystick),
	file(new ofstream()),
	task("JoystickRecorder", (FUNCPTR)WriteData)
{
	// Nothing to do here
}

JoystickRecorder::~JoystickRecorder()
{
	task.Stop();
	
	if (file->is_open())
	{
		file->put('x');
		file->close();
	}
	delete file;
}
	
void JoystickRecorder::Start(char* filename, float recordingInterval, int numberOfAxes, int numberOfButtons)
{
	printf("Recording to %s\n", filename);
	file->open(filename);
	if (!file->is_open())
		cerr << filename << "could not be opened.";
	
	*file << "interval: " << recordingInterval << "\n"
	      << "axes: " << numberOfAxes << "\n"
	      << "buttons: " << numberOfButtons << "\n"
	      << "~\n";
	
	task.Start((int)file, (int)joystick, (int)(recordingInterval * 1000), numberOfAxes, numberOfButtons);
}

void JoystickRecorder::Stop()
{
	printf("Stopping JoystickRecorder");
	task.Stop();
	
	if (file->is_open())
	{
		file->put('x');
		file->close();
	}
}

void JoystickRecorder::WriteData(ofstream* file, GenericHID* joystick, int millisecondInterval, int numberOfAxes, int numberOfButtons)
{
	while (1)
	{
		for (int i = 1; i <= numberOfAxes; i++)
			*file << joystick->GetRawAxis(i) << ",";
		
		for (int i = 1; i <= numberOfButtons; i++)
		{
			if (joystick->GetRawButton(i) == true)
				*file << "T,";
			else
				*file << "F,";
		}
		
		*file << "\n";
		Wait((float)millisecondInterval / 1000);
	}
}
