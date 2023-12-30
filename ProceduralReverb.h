#pragma once

#include <vector>

class ProceduralReverb 
{
public:
    ProceduralReverb(double decayFactor, int delayLength);

    double ProcessSample(double input);

private:
    double decayFactor;
    int delayLength;
    std::vector<double> delayBuffer;
};
