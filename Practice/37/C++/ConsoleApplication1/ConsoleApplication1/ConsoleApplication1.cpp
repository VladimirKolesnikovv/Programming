#include <iostream>
#include "Point.h"
#include <cmath>
using namespace std;

double sqr(double a);
bool equal(double a, double b, double e = 1E-10);



class Vector
{
private:
    Point start, end;
public:
    Vector()
    {
         this->start = Point(0, 0);
         this->end = Point(0, 1);
    }
    Vector(Point end)
    {
        this->start = Point(0, 0);
        this->end = end;
    }
    Vector(Point begin, Point end)
    {
        this->start = begin;
        this->end = end;
    }
    bool operator==(Vector p2)
    {
        if ((this->end.get_x() - this->start.get_x() == p2.end.get_x() - p2.start.get_x()) &&
            (this->end.get_y() - this->start.get_y() == p2.end.get_y() - p2.start.get_y()))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    };
    Vector operator-()
    {
        return Vector (this->end, this->start);
    }
    Vector operator+(Vector p2 )
    {
        Point newVectorStart(this->start.get_x() + p2.start.get_x(), this->start.get_y() + p2.start.get_y());
        Point newVectorEnd(this->end.get_x() + p2.end.get_x(), this->end.get_y() + p2.end.get_y());
        return Vector(newVectorStart, newVectorEnd);
    }
    Vector operator-(Vector p2)
    {
        Point newVectorStart(this->start.get_x() - p2.start.get_x(), this->start.get_y() - p2.start.get_y());
        Point newVectorEnd(this->end.get_x() - p2.end.get_x(), this->end.get_y() - p2.end.get_y());
        return Vector(newVectorStart, newVectorEnd);
    }
    Vector operator*(double k)
    {
        Point newVectorStart(this->start.get_x()*k, this->start.get_y()*k );
        Point newVectorEnd(this->end.get_x()*k, this->end.get_y()*k);
        return Vector(newVectorStart, newVectorEnd);
    }
    double length()
    {
        return  sqrt(pow((this->end.get_x()-this->start.get_x()),2) + pow((this->end.get_y() - this->start.get_y()), 2));
    }
    double operator*(Vector p2)
    {
        double xx, yy;
        xx = (this->end.get_x() - this->start.get_x()) * (p2.end.get_x() - p2.start.get_x());
        yy = (this->end.get_y() - this->start.get_y()) * (p2.end.get_y() - p2.start.get_y());
        return xx + yy ;
    }

};

int main()
{
    Vector a(Point(1, 2)), b(Point(-2, 0), Point(-1, 2));
    if (a == b && b == a) cout << "Equality test passed\n";
    else cout << "Equality test failed\n";

    Vector na(Point(-1, -2)), ox(Point(1, 0)), nox(Point(-1, 0)), oy(Point(0, 1)), noy(Point(0, -1));
    if (a == -na && na == -a && -ox == nox && -oy == noy) cout << "Invert test passed\n";
    else cout << "Invert test failed\n";

    if (ox + oy + oy == a && -ox == -a + oy + oy) cout << "Summation test passed\n";
    else cout << "Summation test failed\n";

    if (-ox + oy == oy - ox && -oy + ox == ox - oy) cout << "Subtraction test passed\n";
    else cout << "Subtraction test failed\n";

    if (ox * 3 == ox + ox + ox &&
        oy * 3 == oy + oy + oy &&
        ox * (-3) == -ox - ox - ox &&
        oy * (-3) == -oy - oy - oy) cout << "Multiplication by number test passed\n";
    else cout << "Multiplication by number test failed\n";

    if (equal(ox.length(), 1) &&
        equal(oy.length(), 1) &&
        equal((ox * 3 + oy * 4).length(), 5)) cout << "Length test passed\n";
    else cout << "Length test failed\n";

    if (equal(ox * ox, sqr(ox.length())) &&
        equal(oy * oy, sqr(oy.length())) &&
        equal((ox * 3 + oy * 4) * (ox * 3 + oy * 4), sqr((ox * 3 + oy * 4).length()))) cout << "Multiplication by Vector test passed\n";
    else cout << "Multiplication by Vector test failed\n";
}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}

double sqr(double a) {
    return a * a;
}