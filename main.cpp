// Copyright (c) 2023 JDSherbert. All rights reserved.
 
#include <cmath>
#include <iostream>
#include <vector>
 
#include "ProceduralReverb.h"
 
// ======================================================================= //
 
// Generates a single sample of a sine wave at the given frequency and time.
// frequency - Hz (e.g. 440.0 = concert A)
// time      - position in seconds (e.g. sampleIndex / sampleRate)
float GenerateInputSignal(float frequency, float time)
{
    return std::sin(2.0f * static_cast<float>(M_PI) * frequency * time);
}
 
// ======================================================================= //
 
int main()
{
    // == Signal Parameters =============================================
    const int   sampleRate = 44100;   // 44.1 kHz
    const float frequency  = 440.0f;  // Concert A
    const float duration   = 0.1f;    // 0.1 seconds — enough to hear the tail
 
    const int numSamples = static_cast<int>(sampleRate * duration);
 
    // == Generate Sine Wave =============================================
    // Each sample index is divided by sampleRate to convert it to seconds.
    // This is then passed to the sine function as the time argument:
    //   sample = sin(2π * frequency * time)
    std::vector<float> sineWave(numSamples);
    for (int i = 0; i < numSamples; ++i)
        sineWave[i] = GenerateInputSignal(frequency, i / static_cast<float>(sampleRate));
 
    // == Set Up Reverb ==================================================
    // decayFactor: how much each reflection attenuates (0.0 - 1.0)
    //              0.5 = moderate decay, tail fades relatively quickly
    // delayLength: number of samples to delay (~11ms at 44100Hz)
    //              500 / 44100 ≈ 0.011 seconds — a small room character
    Sherbert::ProceduralReverb reverb(0.5f, 500);
 
    // == Process and Print ==============================================
    // Print the first 10 samples before and after reverb so the
    // effect of the feedback tail is clearly visible in the output.
    const int printCount = 10;
 
    std::cout << "--- Dry vs Wet (first " << printCount << " samples) ---\n\n";
 
    for (int i = 0; i < printCount; ++i)
    {
        const float dry = sineWave[i];
        const float wet = reverb.ProcessSample(dry);
 
        std::cout << "Sample " << i << "  |  Dry: " << dry << "  |  Wet: " << wet << "\n";
    }
 
    return 0;
}
 
// ======================================================================= //
 
