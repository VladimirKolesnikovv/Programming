#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

int main() 
{
    
    setlocale(LC_ALL, "Russian");

    double a, b, c, x, D, z;
      cout << "Ввести значение a";
    cin >> a;
    cout << "Ввести значение b";
    cin >> b;
    cout << "Ввести значение c";
    cin >> c;

    D = b * b - 4 * a * c;

    if (a == 0 && b == 0)
    {
        if (c == 0)
        {
            cout << "Все корни верны";
        }
        else
        {
            cout << "Нет корней";
        }
    }
    else if (a == 0)
    {
        if (c == 0)
        {
            cout << "Корень уравнения = 0";
        }
        else
        {
            z = -1 * (c / b);
            cout << "Корень = " << z << endl;
        }
    }
    else if (b == 0)
    {
        if (c == 0)
        {
            cout << "Корень уравнения 0";
        }
        else if ((-1 * (c / a)) > 0)
        {
            x = sqrt((-1 * (c / a)));
            cout << "Первый корень равен " << x << endl;
            x = -1 * sqrt((-1 * (c / a)));
            cout << "Второй корень равен " << x << endl;
        }
        else
        {
            cout << "Корней нет";
        }

    }
    else if (c == 0)
    {
        cout << "Первый корень равен" << 0 << endl;
        x = b / a;
        cout << "Второй корень равен " << x << endl;
    }
    else
    {
        if ((D) > 0)
        {
            x = (-1 * b + sqrt(D)) / (2 * a);
            cout << "Первый корень равен " << x << endl;
            x = (-1 * b - sqrt(D)) / (2 * a);
            cout << "Второй корень равен " << x << endl;
        }
        else if ((D) < 0)
        {
            cout << "Корней нет" << endl;
        }
        else
        {
            x = (-1 * b + sqrt(D)) / (2 * a);
            cout << "Корень равен " << x << endl;
        }
    }
    return 0;
}

   


