# webplot

_Web-controlled ESP32 drawing machine using a [Five Bar Linkage Mechanism](https://en.wikipedia.org/wiki/Five-bar_linkage)_

![Robot from above](https://github.com/danja/webplot/raw/main/docs/media/bot-above.jpeg)

An update to [mini-draw](https://github.com/danja/mini-draw) with improved hardware and this time using an ESP32 to allow control over Wifi (from the Web, initially at least using [environs](https://github.com/danja/environs)).

Primary reference has been [Study and Development of Parallel Robots Based On 5-Bar Linkage](https://www.researchgate.net/publication/283356024_Study_and_Development_of_Parallel_Robots_Based_On_5-Bar_Linkage), Manh Tuong Hoang, Trung Tin Vuong, Cong Bang Pham 2015.

## Status

_for detailed updates see [devlog](https://github.com/danja/webplot/blob/main/docs/devlog.md)_

**2022-01-13**

The microcontroller/drawing bot part of the system is working, to an extent. That extent is currently a disappointingly small area. The theoretical drawing area for the configuration I'm using is shown here:

![theoretical coverage](https://github.com/danja/webplot/raw/main/docs/media/theoretical-coverage.png)

What I get is :

![actual coverage](https://github.com/danja/webplot/raw/main/docs/media/drawings.jpeg)

The upper portion of that is the outline I got by manually moving the servos (and some random squiggles). Measuring that, the most useful-looking area was around 14x6 cm. In practice, the best I've achieved so far is the 8x4cm area in the lower portion.
(The spacing between servos is 9.5cm, each of the arms is 12cm).

There are (at least) three factors limiting the area :

1. the limits of the values the equations can operate on (there are a lot of singularities)
2. the physical limits of the arms etc.
3. the behaviour of the servos

**1/** Early experiments made me think there was something trivially wrong with the equations I was using, like a scaling factor. The sums are very twisty so rather than attempting to derive the equations myself I found a completely different version and transcribed those into code to compare. The results were near-enough identical.

**2/** Pushing the arms around (with power off) produced the upper image above

**3/** Initially I was using a power supply that wasn't remotely capable of properly moving the servos. After realising this I put together the supply described below.
I'd naively assumed the servos would have a 180° sweep so initially lined up them up at 90° from the baseline after giving them a 90° location. **Bad move.**
The MG996R servos only have a sweep of ~120° (90° +/- 60°). After measuring x,y and angle values manually I found that the usable area I was after would require a sweep of around 80°. So I attemped to align the servo's 90° direction with the midpoints of the measured angles. There is still quite a discrepancy between the predicted and actual position, so I may revisit this later.

Regarding accuracy, I get the impression that within the useful area, it should be possible to draw recognisable things. There will be some distortion due to the position of the pen relative to the position used in the calculations, but in the drawing above what should be a grid of Xs isn't too far off. This should be fixable in software (I'm unlikely to bother). More significant at the moment is the mechanical instability of the joints, there's a bit of wobble, very evident in this small drawing area. Fixing this properly would require a whole new build (ideally with better tooling). But it's obvious in operation that the servos move quite violently causing shake. I'm pretty sure I can mitigate this by translating movements into smaller stepwise changes separated by short delays, or perhaps more sophisticated [easing](http://robertpenner.com/easing/) (as used in animation).

## Next Steps

I think I can improve behaviour a fair amount by writing a few functions to simply slow down the motion.
But with the hardware kind-of behaving I want to look at the more interesting bits of the software.

First priority is basic I/O to pass commands to the mechanism. An approach that looks promising is to use a [uLisp](http://www.ulisp.com/) interpreter. The start will be to get it to respond to commands on the serial line from a connected computer. From there, move to Web-connected fun.

## References

- [Five-bar linkage](https://en.wikipedia.org/wiki/Five-bar_linkage) (Wikipedia)
- [ESP32](https://en.wikipedia.org/wiki/ESP32) (Wikipedia)

### Local Docs

_[all local ref docs](https://github.com/danja/webplot/tree/main/docs/reference)_

- [Kinematic Analysis of Five-Bar Mechanism in Industrial Robotics](https://github.com/danja/webplot/raw/main/docs/reference/KinematicAnalysisofFive-BarMechanism.pdf), Louis Vathan.B, Hoshila Kumar and Brighton
- [Study and Development of Parallel Robots Based On 5-Bar Linkage](https://github.com/danja/webplot/raw/main/docs/reference/kinematics.pdf), Hoang, Tuong & Vuong, Trung & Pham, Bang, 2015
- [MG996R Servo Datasheet](https://github.com/danja/webplot/raw/main/docs/reference/MG996R-Datasheet.pdf)
- [SG90 Servo Datasheet](https://github.com/danja/webplot/raw/main/docs/reference/sg90_datasheet.pdf)
- [LM317 Voltage Regulator Datasheet](https://github.com/danja/webplot/raw/main/docs/reference/lm317-n.pdf)

## Power Supply

From the [MG996R servo datasheet](https://github.com/danja/webplot/raw/main/docs/reference/MG996R-Datasheet.pdf) :

- Operating voltage: 4.8 V a 7.2 V
- Running Current 500 mA – 900 mA (6V)
- Stall Current 2.5 A (6V)

I had an old (laptop?) switch mode supply offering 12v @ 3A. I also have a bunch of LM317s in TO-220 packages that can potentially handle up to about 2A. When it's not tethered to the computer the ESP32 will also need a 3.3v supply, negligible current.

So from the components I had at hand I put this together on stripboard, with a scrap of aluminium for the heatsink on the 6v side :

![PSU schematic](https://github.com/danja/webplot/raw/main/docs/media/psu2.jpeg)

The circuit is essentially lifted from the [LM317 datasheet](https://github.com/danja/webplot/raw/main/docs/reference/lm317-n.pdf), values tweaked a little. The LED on the output of the 6v should act as a crude indicator of current overload.

![PSU physical](https://github.com/danja/webplot/raw/main/docs/media/psu1.jpeg)
