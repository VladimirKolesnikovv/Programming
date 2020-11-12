#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    double a, b, c;
    char f;
    cout << "Введите условие: цифра-знак-цифра" << endl;
    cin >> a >> f >> b;

    switch (f)
    {
    case '+':
    {
        c = a + b;
        cout << c;
    }
    break;
    case '-':
    {
        c = a - b;
        cout << c;
    }
    break;
    case '*':
    {
        c = a * b;
        cout << c;
    }
    break;
    case '/':
        if (b == 0)
        {
            cout << "Решение невозможно";
        }
        else
        {
            c = a / b;
            cout << c;
        }
        break;

    default:
        cout << "Введите корректный знак вычислений";
    }

    return 0;

}


