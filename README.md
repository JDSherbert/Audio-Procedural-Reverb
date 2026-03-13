![image](https://github.com/JDSherbert/Procedural-Reverb/assets/43964243/86be8436-4593-40d4-bdef-885ac45b1d58)

# Audio: Procedural Reverb

<!-- Header Start -->
<a href = "https://learn.microsoft.com/en-us/cpp/cpp-language"> <img height="40" img width="40" src="https://cdn.simpleicons.org/c++"> </a>
<img align="right" alt="Stars Badge" src="https://img.shields.io/github/stars/jdsherbert/Audio-Procedural-Reverb?label=%E2%AD%90"/>
<img align="right" alt="Forks Badge" src="https://img.shields.io/github/forks/jdsherbert/Audio-Procedural-Reverb?label=%F0%9F%8D%B4"/>
<img align="right" alt="Watchers Badge" src="https://img.shields.io/github/watchers/jdsherbert/Audio-Procedural-Reverb?label=%F0%9F%91%81%EF%B8%8F"/>
<img align="right" alt="Issues Badge" src="https://img.shields.io/github/issues/jdsherbert/Audio-Procedural-Reverb?label=%E2%9A%A0%EF%B8%8F"/>
<img align="right" src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FJDSherbert%2FAudio-Procedural-Reverb%2Fhit-counter%2FREADME&count_bg=%2379C83D&title_bg=%23555555&labelColor=0E1128&title=🔍&style=for-the-badge">
<!-- Header End --> 

-----------------------------------------------------------------------

<a href=""> 
  <img align="left" alt="Audio Processing" src="https://img.shields.io/badge/Audio%20Processing-black?style=for-the-badge&logo=audacity&logoColor=white&color=black&labelColor=black"> </a>
  
<a href="https://choosealicense.com/licenses/mit/"> 
  <img align="right" alt="License" src="https://img.shields.io/badge/License%20:%20MIT-black?style=for-the-badge&logo=mit&logoColor=white&color=black&labelColor=black"> </a>
  
<br></br>

-----------------------------------------------------------------------
 
## Overview
 
A simple procedural reverb implemented in plain C++ using a **comb filter**. Intended as a learning resource for understanding how digital reverb works from first principles — no libraries, no black boxes, just the DSP.
 
Reverb simulates the way sound bounces around a physical space. Rather than recording a real room's impulse response (convolution reverb), procedural reverb *approximates* this behaviour algorithmically, making it lightweight and suitable for real-time audio processing.
 
-----------------------------------------------------------------------
 
## How It Works
 
This implementation uses a single **feedback comb filter**, which is the fundamental building block of most reverb algorithms.
 
```
input ──►──────────────────────────────────────► output
          │                                  ▲
          ▼                                  │
       [ delay buffer (N samples) ] ──► × decayFactor ──►
```
 
On every sample:
 
1. The oldest sample in the delay buffer (N samples ago) is read
2. It is multiplied by `decayFactor` to attenuate it, simulating energy loss
3. This attenuated value is added to the incoming input (feedback)
4. The combined value is written back into the buffer
5. The combined value is returned as output
 
Repeating this on every sample produces a series of exponentially decaying echoes — which our ears interpret as reverberation.
 
The buffer itself is a **circular buffer**: a fixed-size array with a write index that wraps around. This means no memory is ever allocated or freed during audio processing, which is critical for real-time performance.
 
-----------------------------------------------------------------------
 
## Parameters
 
| Parameter | Type | Range | Description |
|---|---|---|---|
| `decayFactor` | `float` | (0.0, 1.0) | How much each reflection attenuates. Near 1.0 = long tail, near 0.0 = very dry. |
| `delayLength` | `size_t` | > 0 | Number of samples to delay. Controls perceived room size. |
 
**Choosing a delay length:**
 
At a 44100Hz sample rate, a useful rule of thumb is:
 
| Delay Length | Approximate Time | Perceived Size |
|---|---|---|
| 2205 | ~50ms | Small room |
| 4410 | ~100ms | Medium room |
| 11025 | ~250ms | Large hall |
| 22050 | ~500ms | Cathedral |
 
-----------------------------------------------------------------------
 
## Files
 
| File | Description |
|---|---|
| `ProceduralReverb.h` | Class declaration and documentation |
| `ProceduralReverb.cpp` | Comb filter implementation |
 
-----------------------------------------------------------------------
 
## Usage
 
### Basic
 
```cpp
// ~100ms delay at 44100Hz, moderate decay
Sherbert::ProceduralReverb reverb(0.75f, 4410);
 
float output = reverb.ProcessSample(input);
```
 
### Wet/Dry Mix
 
`ProcessSample` returns the fully wet signal. Blend it with the dry input yourself to control the mix:
 
```cpp
const float wetAmount = 0.4f; // 0.0 = fully dry, 1.0 = fully wet
 
float wet    = reverb.ProcessSample(input);
float output = (wetAmount * wet) + ((1.0f - wetAmount) * input);
```
 
### Resetting State
 
Call `reset()` when playback stops or the effect is bypassed to prevent stale samples bleeding into the next session:
 
```cpp
reverb.reset();
```
 
### Changing Parameters at Runtime
 
Both parameters can be changed at runtime. Note that either setter internally calls `reset()` to avoid artefacts from the buffer containing samples recorded at the old settings:
 
```cpp
reverb.setDecayFactor(0.9f);  // Longer tail
reverb.setDelayLength(11025); // Larger room
```
 
-----------------------------------------------------------------------
 
## API Reference
 
| Method | Description |
|---|---|
| `ProceduralReverb(decayFactor, delayLength)` | Construct with initial parameters. |
| `ProcessSample(input)` | Process one sample. Call once per sample in your audio loop. |
| `reset()` | Clear the delay buffer and reset the write head. |
| `setDecayFactor(value)` | Update decay factor at runtime. Calls `reset()`. |
| `setDelayLength(value)` | Update delay length at runtime. Calls `reset()`. |
| `getDecayFactor()` | Returns current decay factor. |
| `getDelayLength()` | Returns current delay length in samples. |
 
-----------------------------------------------------------------------
 
## Limitations & Next Steps
 
This is an intentionally minimal implementation for learning purposes. A single comb filter is a good starting point but has limitations worth knowing about:
 
**Metallic colouration**: a single comb filter produces a characteristic "metallic" or "pitched" resonance because the echoes are evenly spaced. Real reverb algorithms (like the Schroeder reverberator) use multiple comb filters at prime-number delay lengths to break up this regularity.
 
**No early reflections**: real rooms produce a burst of distinct early reflections before the diffuse reverb tail begins. This implementation goes straight to the tail.
 
**No diffusion**: allpass filters are typically chained after comb filters to scatter the echo density and produce a smoother, more natural tail.
 
If you want to explore further, the natural next steps from here are:
- Multiple parallel comb filters (Schroeder reverberator)
- Allpass filter diffusion stages
- Separate early reflection delay lines
- High-frequency damping (a low-pass filter in the feedback path)
 
-----------------------------------------------------------------------
 
