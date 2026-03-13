// Copyright (c) 2023 JDSherbert. All rights reserved.
 
#include "ProceduralReverb.h"
 
#include <cassert>
#include <cmath>
 
// ======================================================================= //
 
Sherbert::ProceduralReverb::ProceduralReverb(float decayFactor, size_t delayLength)
    : decayFactor(std::clamp(decayFactor, 0.0f, 0.9999f))
    , delayLength(delayLength)
    , writeIndex(0)
{
    assert(delayLength > 0);
    delayBuffer.resize(delayLength, 0.0f);
}
 
// ======================================================================= //
 
float Sherbert::ProceduralReverb::ProcessSample(float input)
{
    // ─── HOW A COMB FILTER WORKS ─────────────────────────────────────────
    //
    // A comb filter adds a delayed, attenuated copy of the signal to itself.
    // Repeating this on every sample creates a series of echoes that decay
    // exponentially, which our ears perceive as reverberation.
    //
    // On each call we:
    //   1. Read the oldest sample from the buffer (the delayed signal)
    //   2. Attenuate it by decayFactor to simulate energy loss
    //   3. Feed the attenuated delay back into the input (feedback)
    //   4. Write the new combined sample into the buffer
    //   5. Return the combined sample as output
    //
    // The write index advances circularly so no memory is ever allocated
    // or freed during processing — the buffer is fixed at construction.
    // ─────────────────────────────────────────────────────────────────────
 
    // Read the oldest sample (delayLength samples ago)
    const float delayedSample = delayBuffer[writeIndex];
 
    // Attenuate the delayed sample and feed it back into the input
    const float feedbackSample = input + (delayedSample * decayFactor);
 
    // Write the new sample into the buffer at the current write position
    delayBuffer[writeIndex] = feedbackSample;
 
    // Advance the write index, wrapping around at the end of the buffer
    writeIndex = (writeIndex + 1) % delayLength;
 
    return feedbackSample;
}
 
// ======================================================================= //
 
void Sherbert::ProceduralReverb::reset()
{
    std::fill(delayBuffer.begin(), delayBuffer.end(), 0.0f);
    writeIndex = 0;
}
 
// ======================================================================= //
 
void Sherbert::ProceduralReverb::setDecayFactor(float newDecayFactor)
{
    // Limit to 0.0f and < 1.0f to prevent infinite decaying
    decayFactor = std::clamp(newDecayFactor, 0.0f, 0.9999f);
    reset();
}
 
// ======================================================================= //
 
void Sherbert::ProceduralReverb::setDelayLength(size_t newDelayLength)
{
    assert(newDelayLength > 0);
    delayLength = newDelayLength;
    delayBuffer.resize(delayLength, 0.0f);
    reset();
}
 
// ======================================================================= //
