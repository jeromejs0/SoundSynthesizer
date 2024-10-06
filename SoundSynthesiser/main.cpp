#include <iostream>
#include "olcNoiseMaker.h"
using namespace std;

atomic<double> dFrequencyOutput = 0.0;

double MakeNoise(double dTime) { // this arg is the time passed since the start of the program

	double dOutput = 0.1 * sin(dFrequencyOutput * 2 * 3.14159 * dTime);
	
	if(dOutput > 0.0) {
		return 0.2;

	}
	else {
		return -0.2;
	}
	

		
	return 0.5 * sin(440.0 * 2 * 3.14159 * dTime);
}


int main() {

	wcout << "Synthesiser version 1" << endl;

	// Get all sound hardeare
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	// Display findings
	for (auto d : devices) wcout << "Found Output Device:" << d << endl;

	// Create sound machine!!
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	// Link noise function with sound machine (create function pointer)
	sound.SetUserFunction(MakeNoise);

	while (1) {
		
		// Add a keyboard

		if (GetAsyncKeyState('A') & 0x8000) {
			dFrequencyOutput = 440.0;
		}
		else {
			dFrequencyOutput = 0.0;
		}
	}

	return 0;
}