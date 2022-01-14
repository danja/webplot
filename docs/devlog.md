**2022-01-13**

https://eightytwo.net/blog/running-ulisp-on-an-esp32/

https://github.com/technoblogy/ulisp-esp

**2021-01-05**

Hardware sorted: beefier servos (MG996R) driving the arms, new design of pen lifter.

Attached to the ESP32. Note madhephaestus/ESP32Servo needed rather than the default Arduino lib.

Took a little while - for some reason it didn't like the GPIOs I'd initially chosen, also the new SG90 I'd put in the pen lifter turned out to be a dud.

Turned out I hadn't got very far with the code with mini-draw. But I've now transcribed the inverse kinematic equations into Python, made a rough plotting function to sanity check. After realising I was mixing degrees and radians (!!!) and discovering I'd missed a '-' sign from one equation, it now seems valid. **LINK** . /sums subdirectory, inverse.ipynb

I used a Jupyter Notebook in VSCode, that worked really nicely.

Next I need to port that across to C++ for the ESP32, figure out some basic comms to pass commands over serial.

An issue I'll have to deal with right away is dealing with invalid input - lots of x,y values will simply not work.

Looking ahead a little, I want to be able to pass data to the thing over the Web. SVG would probably be the most elegant solution, but not sure I can be bothered figuring out the translation (it's probably a decade since I last parsed XML). An approach that should be easier and potentially a lot more fun, is to use a uLisp interpreter on the ESP32.

Also need to look at HTTP client libs for the ESP32. I think I've played with before, but totally forgotten.

**2022-01-03**

This repo set up. I've got most of the hardware ready from previous experiments. Hopefully I can lift most of the inverse kinematics code from [mini-draw](https://github.com/danja/mini-draw).
