#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

long double fact(int a)
{
    if (a < 0)
        return 0;
    if (a == 0)
        return 1;
    else
        return a * fact(a - 1);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int a;
    cout << "Введите число" << endl;
    cin >> a;
    cout << "Факториал числа" << " " << a << " = " << fact(a) << endl;
    return 0;
}
