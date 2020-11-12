#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    double a, b, c, x1, x2, x3, y1, y2, y3, p, S, z, k;
    //p - полупериметр треугольника, S - площадь фигуры, k - свойство треугольника

    cout << "Для использования сторон введите 1, для метода координат введите 2" << endl;
    cin >> n;
    switch (n)
    {
    case 1:
    {
        cout << "Заполните значение а " << endl;
        cin >> a;
        cout << "Заполните значение b " << endl;
        cin >> b;
        cout << "Заполните значение c " << endl;
        cin >> c;
        if ((a < b + c) && (b < a + c) && (c < a + b))
        {
            p = (a + b + c) / 2;
            S = sqrt(p * (p - a) * (p - b) * (p - c));
            cout << "S = " << S;
        }
        else
        {
            cout << "Несуществующий треугольник";
        }
    }
    break;
    case 2:
    {
        cout << "Координаты точки A " << endl;
        cin >> x1 >> y1;
        cout << "Координаты точки B " << endl;
        cin >> x2 >> y2;
        cout << "Координаты точки C " << endl;
        cin >> x3 >> y3;
        a = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
        b = sqrt(((x3 - x2) * (x3 - x2)) + ((y3 - y2) * (y3 - y2)));
        c = sqrt(((x3 - x1) * (x3 - x1)) + ((y3 - y1) * (y3 - y1)));
        if ((a < b + c) && (b < a + c) && (c < a + b))
        {
            p = (a + b + c) / 2;
            S = sqrt(p * (p - a) * (p - b) * (p - c));
            cout << "S = " << S;
        }
        else
        {
            cout << "Несуществующий треуголник";
        }
    }
    break;
    default:
        cout << ("Некорректный ввод");
    }


}

