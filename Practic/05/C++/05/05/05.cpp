#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    double l, x, v, t, a, g;
    a = g = 9.8;
    cout << "Начальное положение объекта, время движения и началная скорость";
        cin >> x >> t >> v;
    
    l = (x + v * t) - (a * t * t / 2);
    cout << "\n Расстояние = " << abs(l);
}
