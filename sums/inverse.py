# HOW DID THIS EVER WORK!

# 5-Bar Linkage : Inverse Kinematics
#
# from Study and Development of Parallel Robots Based On 5-Bar Linkage
# Manh Tuong Hoang, Trung Tin Vuong, Cong Bang Pham 2015
# https://www.researchgate.net/publication/283356024_Study_and_Development_of_Parallel_Robots_Based_On_5-Bar_Linkage

import math
import numpy as np

import matplotlib.pyplot as plt

base = 10 # distance between servos, lc in the paper ^^
humerus = 10 # from each servo to elbow, la ^^
radius = 10 # elbow to pen, lb ^^

baselineX = np.linspace(0, base, 100)
baselineY = np.zeros(100)

xArray = np.linspace(-100, 100, 100)
yArray = np.linspace(-100, 100, 100)

for x in xArray:
    for y in yArray:
        E1 = -2*humerus*x
        F1 = -2*humerus*y
        G1 = humerus*humerus-radius*radius+x*x+y*y
        E4 = 2*humerus*(base-x)
        F4 = 2*humerus*y
        G4 = base*base + humerus*humerus - radius*radius + x*x + y*y - 2*base*x

        lumpD1plus = (-F1+math.sqrt(E1*E1+F1*F1-G1*G1))/(G1-E1)
        lumpD1minus = (-F1-math.sqrt(E1*E1+F1*F1-G1*G1))/(G1-E1)
        lumpD4plus = (-F4+math.sqrt(E4*E4+F4*F4-G4*G4))/(G4-E4)
        lumpD4minus = (-F4-math.sqrt(E4*E4+F4*F4-G4*G4))/(G4-E4)

        D1plus = 2*math.atan(lumpD1plus)
        D1minus = 2*math.atan(lumpD1minus)
        D4plus = 2*math.atan(lumpD4plus)
        D4minus = 2*math.atan(lumpD4minus)
