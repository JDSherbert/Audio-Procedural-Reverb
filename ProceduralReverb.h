// Copyright (c) 2023 JDSherbert. All rights reserved.
 
#pragma once
 
#include <algorithm>
#include <vector>
 
// ======================================================================= //
// ProceduralReverb
//
// A simple comb filter reverb. A comb filter works by feeding a delayed,
// attenuated copy of the signal back into itself repeatedly, simulating
// the way sound bounces off walls and decays over time.
//
// The delay length controls the "room size" (longer delay = larger room),
// and the decay factor controls how quickly the tail fades out.
//
// Usage:
//   ProceduralReverb reverb(0.75f, 4410);  // 0.1s delay at 44100Hz
//   float output = reverb.ProcessSample(input);
//
// ======================================================================= //
 
namespace Sherbert
{
 
    class ProceduralReverb
    {

    public:
 
        // ------------------------------------------------------------------
        // Constructor
        //
        // decayFactor  - How much each reflection attenuates (0.0 - 1.0).
        //                Values closer to 1.0 produce a longer tail.
        //                Values closer to 0.0 produce a very short, dry tail.
        //                Must be in range (0.0, 1.0) to avoid silence or feedback.
        //
        // delayLength  - Number of samples to delay the signal.
        //                This determines the perceived room size.
        //                At 44100Hz sample rate: 4410 = ~0.1s, 22050 = ~0.5s.
        //                Must be greater than zero.
        // ------------------------------------------------------------------
 
        ProceduralReverb(float decayFactor, size_t delayLength);
 
        // ------------------------------------------------------------------
        // ProcessSample
        //
        // Call this once per sample in your audio callback loop.
        // Feeds the input through the comb filter and returns the wet output.
        //
        // For a wet/dry mix, blend the output with the original input:
        //   float wet = 0.5f;
        //   float result = (wet * reverb.ProcessSample(input)) + ((1.0f - wet) * input);
        // ------------------------------------------------------------------
 
        float ProcessSample(float input);
 
        // ------------------------------------------------------------------
        // Reset
        //
        // Clears the delay buffer and resets the write head.
        // Call this when playback stops or the effect is bypassed to avoid
        // stale samples bleeding into the next playback session.
        // ------------------------------------------------------------------
 
        void reset();
 
        // ------------------------------------------------------------------
        // Getters / Setters
        // ------------------------------------------------------------------
 
        float getDecayFactor() const noexcept { return decayFactor; }
        size_t getDelayLength() const noexcept { return delayLength; }
 
        // Note: changing these at runtime will call reset() to avoid artefacts
        // from the buffer containing samples recorded at the old settings.
        void setDecayFactor(float newDecayFactor);
        void setDelayLength(size_t newDelayLength);
 
    private:
 
        float  decayFactor;
        size_t delayLength;
 
        std::vector<float> delayBuffer;
        size_t writeIndex = 0;
 
    };
 
}
 
// ======================================================================= //
