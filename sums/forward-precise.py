# 5-Bar Linkage : Forward Kinematics
#
# from Study and Development of Parallel Robots Based On 5-Bar Linkage
# Manh Tuong Hoang, Trung Tin Vuong, Cong Bang Pham 2015
# https://www.researchgate.net/publication/283356024_Study_and_Development_of_Parallel_Robots_Based_On_5-Bar_Linkage

import math
import numpy as np
import mpmath
from mpmath import mp, mpf, fp
import matplotlib.pyplot as plt

mpmath.mp.dps = 1000 # decimal places

nPoints = 100

base = mpf(10) # distance between servos
humerus = mpf(10) # from each servo to elbow
radius = mpf(10) # elbow to pen

angleMin = mpf(60 * mpmath.pi/180)
angleMax = mpf(120 * mpmath.pi/180)

anglesL = mpmath.linspace(angleMin, angleMax, nPoints)
anglesR = mpmath.linspace(angleMin, angleMax, nPoints)

baselineX = mpmath.linspace(0, base, 100)
baselineY = mpmath.zeros(100, 1)

plt.style.use('seaborn-whitegrid')
fig, ax = plt.subplots()
plt.grid(True)

two = mpf(2)
print(type(two))

xMin, xMax, yMin, yMax = 0 

for angleL in anglesL:
    for angleR in anglesR:
        E = two*radius*(base+humerus*(mpmath.cos(angleR)-mpmath.cos(angleL)))
        F = two*humerus*radius*(mpmath.sin(angleR)-mpmath.sin(angleL))
        G = base*base+two*humerus*humerus+two*base*humerus*mpmath.cos(angleR)-two*humerus*humerus*mpmath.cos(angleR-angleL)

        if G-E != 0 and E*E+F*F-G*G > 0: # avoid div by zero, sqrt of negative

            lumpXplus =  (-F+mpmath.sqrt(E*E+F*F-G*G)) / (G-E)
            lumpXminus = (-F-mpmath.sqrt(E*E+F*F-G*G)) / (G-E)
            lumpYplus =  (-F+mpmath.sqrt(E*E+F*F-G*G)) / (G-E)
            lumpYminus = (-F-mpmath.sqrt(E*E+F*F-G*G)) / (G-E)
            
            xPlus =  base+humerus*mpmath.cos(angleR)+radius*mpmath.cos(two*mpmath.atan(lumpXplus))
            xMinus = base+humerus*mpmath.cos(angleR)+radius*mpmath.cos(two*mpmath.atan(lumpXminus))
            
            yPlus =  humerus*mpmath.sin(angleR)+radius*mpmath.sin(two*mpmath.atan(lumpYplus))
            yMinus = humerus*mpmath.sin(angleR)+radius*mpmath.sin(two*mpmath.atan(lumpYminus))
        
            ax.plot(xMinus, yMinus, 'o', color='blue')
            ax.plot(xMinus, yPlus, 'o', color='green')
            ax.plot(xPlus, yMinus, 'o', color='red')
            ax.plot(xPlus, yPlus, 'o', color='yellow')
            
            
ax.plot(baselineX, baselineY, color='black')
plt.show()
