// ©2023 JDSherbert. All rights reserved.
#include "ProceduralReverb.h"

#include <cmath>

ProceduralReverb::ProceduralReverb(double decayFactor, int delayLength)
    : decayFactor(decayFactor)
    , delayLength(delayLength) 
{
    delayBuffer.resize(delayLength, 0.0);
}

double ProceduralReverb::ProcessSample(double input) 
{
    delayBuffer.push_back(input);

    for (int i = 0; i < delayBuffer.size(); ++i) 
    {
        delayBuffer[i] *= decayFactor;
    }

    double output = 0.0;
    for (int i = 0; i < delayBuffer.size(); ++i) 
    {
        output += delayBuffer[i];
    }

    delayBuffer.erase(delayBuffer.begin());

    return output;
}
