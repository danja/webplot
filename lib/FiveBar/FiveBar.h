#ifndef FiveBar_h
#define FiveBar_h

#include <Point.h>

class FiveBar
{
public:
    FiveBar(float base, float proximal, float distal);
    Point inverseKinematic(Point pen);
    float deg(float r);

private:
    float base,
        proximal,
        distal;
};

#endif