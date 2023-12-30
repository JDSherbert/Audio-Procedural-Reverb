// ©2023 JDSherbert. All rights reserved.
#include "ProceduralReverb.h"

#include <cmath>

ProceduralReverb::ProceduralReverb(double decayFactor, int delayLength)
    : decayFactor(decayFactor)
    , delayLength(delayLength) 
{
    // Initialize delay buffer with 0
    delayBuffer.resize(delayLength, 0.0);
}

// Apply reverb effect to an input signal
double ProceduralReverb::ProcessSample(double input) 
{
    // Add the input to the delay buffer
    delayBuffer.push_back(input);

    // Apply decay to existing samples in the delay buffer
    for (int i = 0; i < delayBuffer.size(); ++i) 
    {
        delayBuffer[i] *= decayFactor;
    }

    // Get the output by summing the delayed samples
    double output = 0.0;
    for (int i = 0; i < delayBuffer.size(); ++i) 
    {
        output += delayBuffer[i];
    }

    // Remove the oldest sample from the delay buffer
    delayBuffer.erase(delayBuffer.begin());

    return output;
}
