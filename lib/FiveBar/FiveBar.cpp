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

// from Kinematic Analysis of Five-Bar Mechanism in Industrial Robotics
Point FiveBar::inverseKinematic2(Point pen)
{
    double l1 = proximal;
    double l2 = distal;
    double l3 = distal;
    double l4 = proximal;
    double l5 = base;

    double A1 = pen.x;
    double B1 = pen.y;
    double C1 = (l1 * l1 - l2 * l2 + pen.x * pen.x + pen.y * pen.y) / (2.0 * l1);

    // out of range defaults
    double angleL = -1;
    double angleR = -1;

    if ((A1 * A1 + B1 * B1 - C1 * C1) > 0 && (-A1 - C1) != 0)
    {
        double lumpD1minus = (-B1 - sqrt(A1 * A1 + B1 * B1 - C1 * C1)) / (-A1 - C1);
        double D1minus = 2.0 * atan(lumpD1minus);

        double lumpD1plus = (-B1 + sqrt(A1 * A1 + B1 * B1 - C1 * C1)) / (-A1 - C1);
        double D1plus = 2.0 * atan(lumpD1plus);

        angleL = deg(D1minus);
    }

    double A2 = pen.x - l5;
    double B2 = pen.y;
    double C2 = (l4 * l4 + l5 * l5 - l3 * l3 - 2.0 * pen.x * l5 + pen.x * pen.x + pen.y * pen.y) / (2.0 * l4);

    if ((A2 * A2 + B2 * B2 - C2 * C2) > 0 && (-A2 - C2) != 0)
    {
        double lumpD4minus = (-B2 - sqrt(A2 * A2 + B2 * B2 - C2 * C2)) / (-A2 - C2);
        double D4minus = 2.0 * atan(lumpD4minus);

        double lumpD4plus = (-B2 + sqrt(A2 * A2 + B2 * B2 - C2 * C2)) / (-A2 - C2);
        double D4plus = 2.0 * atan(lumpD4plus);

        angleR = deg(D4plus);
    }
    return Point(angleL, angleR);
}

// as 1 with atan2
Point FiveBar::inverseKinematic3(Point pen)
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

    double rooted = E1 * E1 + F1 * F1 - G1 * G1;
    if (rooted < 0)
    {
        rooted = -rooted;
    }
    if ((G1 - E1) != 0)
    {
        double y = (-F1 + sqrt(rooted));
        double x = (G1 - E1);

        double D1plus = 2 * atan2(y, x);
        // double lumpD1plus = (-F1 + sqrt(E1 * E1 + F1 * F1 - G1 * G1)) / (G1 - E1);
        // double D1plus = 2 * atan(lumpD1plus);
        //  double lumpD1minus = (-F1 - sqrt(E1 * E1 + F1 * F1 - G1 * G1)) / (G1 - E1);
        //  double D1minus = 2 * atan(lumpD1minus);
        angleL = deg(D1plus);
    }

    rooted = E4 * E4 + F4 * F4 - G4 * G4;
    if (rooted < 0)
    {
        rooted = -rooted;
    }
    if ((G4 - E4) != 0)
    {
        // double lumpD4plus = (-F4 + sqrt(E4 * E4 + F4 * F4 - G4 * G4)) / (G4 - E4);
        // double D4plus = 2 * atan(lumpD4plus);

        // double lumpD4minus = (-F4 - sqrt(E4 * E4 + F4 * F4 - G4 * G4)) / (G4 - E4);
        // double D4minus = 2 * atan(lumpD4minus);
        double y = (-F4 - sqrt(rooted));
        double x = (G4 - E4);
        double D4minus = 2 * atan2(y, x);
        angleR = deg(D4minus);
    }
    return Point(angleL, angleR);
}

double FiveBar::deg(double r)
{
    return r * (180.0 / 3.141592653589793238463);
}
