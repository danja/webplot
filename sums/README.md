## Using the files

Python 3 is used throughout. 

[Anaconda](https://www.anaconda.com/products/individual) seems the easiest way of getting a controlled Python environment running.

Running anaconda-navigator and then launching JupyterLab will allow running of the Jupyter Notebook files.

## Simulation

The paper [Study and Development of Parallel Robots based on 5-Bar Linkage](https://www.researchgate.net/publication/283356024_Study_and_Development_of_Parallel_Robots_Based_On_5-Bar_Linkage) (Manh Tuong Hoang, Trung Tin Vuong, Cong Bang Pham) includes analysis of these systems. Two parts are of particular interest. The *forward kinematic* gives the x,y position of the pen given the angles of the servos. The *inverse kinematic* gives the angles of the servos give the x, y position of the pen.

The inverse kinematic will be a significant part of the Arduino code. But before getting to that, the forward kinematic should be useful in determining optimal proportions of the system to allow drawing on a reasonable large rectangle.

I've coded up the forward kinematic in Python (with matplotlib for diagrams) with *moderate* success. Wikipedia gives a diagram for the area covered by a 5-bar linkage:

![velocity ellipses](https://github.com/danja/mini-draw/blob/main/images/velocity-ellipses.png?raw=true)

My simulation came out rather different :

![imprecise 360 forward](https://github.com/danja/mini-draw/blob/main/images/forward-360.png?raw=true)

But restricting the range of of servo angles to 90 +/-10 degrees gave a plot that showed I was probably on the right track:

![limited forward](https://github.com/danja/mini-draw/blob/main/images/limited.png?raw=true)

(The blob at the bottom is what happens when the arms bend inwards, correct here but not desirable in the physical version).

Making the angles vary 60-120 degrees gave something a little better, but strangely skewed - it should be symmetric :

![forward](https://github.com/danja/mini-draw/blob/main/images/imprecise.png?raw=true)


The calculations are quite long-winded so my guess was the distortion was down to inadequate precision in my code. But I modified the code to use the ```mpmath``` library, I believe using 1,000 decimal places (!) and still got a strange result.  

![forward](https://github.com/danja/mini-draw/blob/main/images/precise_10-10-10.png?raw=true)

Noting that the top-right quadrant of my results appeared pretty much how it should be -

![cropped](https://github.com/danja/mini-draw/blob/main/images/precise-cropped.png)

I revised the [code](https://github.com/danja/mini-draw/tree/main/sums) just to show this corner and flip it. Very hacky, but did allow a bit of progress. Unfortunately, when I returned to the Jupyter Notebook later, it'd stopped working - I must have had some global variables lurking before... So I'm leaving that for now.
