// ©2023 JDSherbert. All rights reserved.

#include <iostream> // For debug printing
#include <cmath> // For M_PI

#include "ProceduralReverb.h"

// Function to generate a simple input signal (for demonstration purposes)
double GenerateInputSignal(double frequency, double time)
{
    return sin(2.0 * M_PI * frquency * time);
}

int main() 
{
    // Setup parameters for the reverb
    double decayFactor = 0.5;
    int delayLength = 500;

    ProceduralReverb reverb(decayFactor, delayLength); // Create a reverb object

    // Begin simulation of reverb
    for (int i = 0; i < 1000; ++i) 
    {
        // Process input signal with reverb
        double outputSignal = reverb.processSample(GenerateInputSignal(440.0f, i / 44100.0f));
        /* In the context of this example, we're generating a sinusoidal signal with a frequency of 440.0 Hertz;
         * this division scales the loop index to represent time in seconds. 
         * The formula for calculating the angle (argument) of the sine function is typically given as 2 * π * frequency * time. 
         * In this case, time is derived by dividing the loop index (i) by the sample rate (44100).
         */

        std::cout << outputSignal << std::endl;
    }

    return 0;
}
