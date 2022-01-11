#include <cmath>
#include <FiveBar.h>
#include <Point.h>

// http://www.cplusplus.com/reference/cmath/

FiveBar::FiveBar(double _base, double _proximal, double _distal)
{
    base = _base;         // distance between servos, lc in the paper ^^
    proximal = _proximal; // from each servo to elbow, la ^^
    distal = _distal;     // elbow to pen, lb ^^
}

Point FiveBar::inverseKinematic(Point pen)
{
    double E1 = -2.0 * proximal * pen.x;
    double F1 = -2.0 * proximal * pen.y;
    double G1 = proximal * proximal - distal * distal + pen.x * pen.x + pen.y * pen.y;
    double E4 = 2.0 * proximal * (base - pen.x);
    double F4 = -2.0 * proximal * pen.y;
    double G4 = base * base + proximal * proximal - distal * distal + pen.x * pen.x + pen.y * pen.y - 2.0 * base * pen.x;

    // out of range defaults
    double angleL = -1.0;
    double angleR = -1.0;

    // 'lump..' is the equation inside the arctan
    //  D1plus etc. are the resulting angles
    if ((E1 * E1 + F1 * F1 - G1 * G1) > 0 && (G1 - E1) != 0)
    {
        double lumpD1plus = (-F1 + sqrt(E1 * E1 + F1 * F1 - G1 * G1)) / (G1 - E1);
        double D1plus = 2 * atan(lumpD1plus);
        //  double lumpD1minus = (-F1 - sqrt(E1 * E1 + F1 * F1 - G1 * G1)) / (G1 - E1);
        //  double D1minus = 2 * atan(lumpD1minus);
        angleL = deg(D1plus);
    }

    if ((E4 * E4 + F4 * F4 - G4 * G4) > 0 && (G4 - E4) != 0)
    {
        // double lumpD4plus = (-F4 + sqrt(E4 * E4 + F4 * F4 - G4 * G4)) / (G4 - E4);
        // double D4plus = 2 * atan(lumpD4plus);
        double lumpD4minus = (-F4 - sqrt(E4 * E4 + F4 * F4 - G4 * G4)) / (G4 - E4);
        double D4minus = 2 * atan(lumpD4minus);
        angleR = deg(D4minus);
    }
    return Point(angleL, angleR);
}

double FiveBar::deg(double r)
{
    return r * (180.0 / 3.141592653589793238463);
}
