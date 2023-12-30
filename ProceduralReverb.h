// ©2023 JDSherbert. All rights reserved.

#pragma once

#include <vector>

class ProceduralReverb 
{
public:

    ProceduralReverb(double decayFactor, int delayLength);

    double ProcessSample(double input);

private:

    double decayFactor; // Decay factor for each delayed sample
    int delayLength; // Length of the delay buffer
    std::vector<double> delayBuffer; // Buffer to store delayed samples
};
