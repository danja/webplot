For various reasons (mostly fun) I've rebuilt my drawing robot. Same arms, but improved pen lifter, much heftier servos driving the arms and an ESP32 rather than an Arduino for the processor.
Now for the code, which I stalled of last time as the previous hardware wasn't really up to it.

But I have a puzzle...

The main part of the software needed is the 'inverse kinematics'. This will translate the angles of the left, right servos into the required x, y of the drawing area. Even with this simple-looking 5-bar mechanism (the spacing between the servos is the 5th bar), the calculations are very scary trigonometry. Fortunately other folks have already worked that out, so I just need to put it into code and tweak to work with my setup.

But last night, when testing the thing, the movements of the beefy servos can get a bit violent. So I was looking at smoothing algorithms. The obvious one, is just to chop a movement from one point to another into smaller steps, have a tiny delay between each.
 
But while reading around I can across 'Penner Easing', where you make the movements non-linear : start slow, speed up for the middle of a move, slow down towards the end.

I can see this working fine with just one servo moving, but what's puzzling me is when you have two or more. If you want to draw a straight line from (x1, y1) to (x2, y2) but the movements over x & y are non-linear, will the line still be straight? (Assuming x & y both have the same function applied). My intuition suggests 'sometimes, depending on the function'. Not sure I can be bothered doing the sums to check the conditions... 

I think in the first instance I'll just go for 'slow', so (I think) the line will be made of shorter lines with the same slope, ie, the same. But must play with non-linear.
The non-linear won't matter when the pen is up (moving not drawing), so I guess that might be worth doing whatever the other case.
   


 

   
