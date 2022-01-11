#ifndef FiveBar_h
#define FiveBar_h

#include <Point.h>

class FiveBar
{
public:
    FiveBar(double base, double proximal, double distal);
    Point inverseKinematic(Point pen);
    Point inverseKinematic2(Point pen);
    double deg(double r);

private:
    double base,
        proximal,
        distal;
};

#endif