#ifndef Point_h
#define Point_h

class Point
{
private:
    //

public:
    float x, y;
    Point() : x(0), y(0) {}
    Point(float x, float y) : x(x), y(y) {}
};

class Line
{
private:
    Point p1;
    Point p2;

public:
    Line(const Point &p1, const Point &p2) : p1(p1), p2(p2) {}

    void setPoints(const Point &ap1, const Point &ap2)
    {
        p1 = ap1;
        p2 = ap2;
    }
};

#endif