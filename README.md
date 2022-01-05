# webplot

_Web-controlled ESP32 drawing machine_

An update to [mini-draw](https://github.com/danja/mini-draw) with improved hardware and this time using an ESP32 to allow control over Wifi (from the Web, initially at least using [environs](https://github.com/danja/environs)).

Primary reference has been [Study and Development of Parallel Robots Based On 5-Bar Linkage](https://www.researchgate.net/publication/283356024_Study_and_Development_of_Parallel_Robots_Based_On_5-Bar_Linkage), Manh Tuong Hoang, Trung Tin Vuong, Cong Bang Pham 2015.

## Status

_for detailed updates see [devlog](https://github.com/danja/webplot/blob/main/docs/devlog.md)_

**2022-01-05**

Hardware seems functional, connected to ESP32.

I transcribed the inverse kinematic equations into Python, made a rough plotting function to sanity check. **LINK**

After realising I was mixing degrees and radians (!!!) and discovering I'd missed a '-' sign from one equation, it now seems valid.

Next I need to port that across to C++ for the ESP32, figure out some basic comms to pass commands over serial.
