![image](https://github.com/JDSherbert/Procedural-Reverb/assets/43964243/86be8436-4593-40d4-bdef-885ac45b1d58)

# Procedural Reverb

<!-- Header Start -->
<a href = "https://learn.microsoft.com/en-us/cpp/cpp-language"> <img height="40" img width="40" src="https://cdn.simpleicons.org/c++"> </a>
<img align="right" alt="Stars Badge" src="https://img.shields.io/github/stars/jdsherbert/Procedural-Reverb?label=%E2%AD%90"/>
<img align="right" alt="Forks Badge" src="https://img.shields.io/github/forks/jdsherbert/Procedural-Reverb?label=%F0%9F%8D%B4"/>
<img align="right" alt="Watchers Badge" src="https://img.shields.io/github/watchers/jdsherbert/Procedural-Reverb?label=%F0%9F%91%81%EF%B8%8F"/>
<img align="right" alt="Issues Badge" src="https://img.shields.io/github/issues/jdsherbert/Procedural-Reverb?label=%E2%9A%A0%EF%B8%8F"/>
<img align="right" src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FJDSherbert%2FProcedural-Reverb%2Fhit-counter%2FREADME&count_bg=%2379C83D&title_bg=%23555555&labelColor=0E1128&title=🔍&style=for-the-badge">
<!-- Header End --> 

-----------------------------------------------------------------------
  
<a href="https://choosealicense.com/licenses/mit/"> 
  <img align="right" alt="License" src="https://img.shields.io/badge/License%20:%20MIT-black?style=for-the-badge&logo=mit&logoColor=white&color=black&labelColor=black"> </a>
  
<br></br>

-----------------------------------------------------------------------
## Overview
Reverb, short for reverberation, is a crucial aspect of audio processing that simulates the reflections of sound in an environment. When a sound is produced in a physical space, it doesn't just reach the listener directly; it also bounces off surfaces, creating reflections. These reflections combine with the direct sound to produce the characteristic reverberant field that defines the acoustic signature of a space.

Procedural reverb is a method of simulating this complex phenomenon algorithmically. While physical spaces exhibit intricate reverb characteristics, simulating them in real-time audio processing often involves computationally expensive operations. Procedural reverb, as opposed to convolution reverb (which is based on real impulse responses), uses algorithms to approximate the reverb effect. This makes it more suitable for scenarios where computational resources are limited.

The procedural reverb implemented here is a basic example and serves as an introduction to the concept. In a more advanced setting, procedural reverb algorithms often involve more intricate mathematical models, multiple delay lines, feedback networks, and various types of filtering to mimic the complexity of real-world reverberation.

![image](https://github.com/JDSherbert/Procedural-Reverb/assets/43964243/602a5d56-3dd6-4c27-b097-08136c468f53)

### Key Components of Procedural Reverb

#### 1. Delay Line: 
The delayBuffer in the code represents a simple delay line. Incoming samples are stored and decayed over time, simulating the multiple reflections of sound in a reverberant space.

#### 2. Decay Factor: 
The decayFactor controls how quickly the reflections decay. Higher decay factors result in faster decay, simulating a more absorbent environment.

#### 3. Main Loop: 
The processing loop iterates over the delay line, applying decay to each sample and summing them to create the reverb effect. Old samples are then removed from the delay line.


-----------------------------------------------------------------------

