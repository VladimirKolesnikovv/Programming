#include <iostream>
#include <locale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    double a, b, c;
    cout << "Введите первое число";
    cin >> a;
    cout << "Введите второе число";
    cin >> b;
    c = a;
    a = b;
    b = c;
    cout << "\n Первое число" << a << "\n Второе число" << b <<endl;

    double y, z;
    cout << "Введите первое число";
    cin >> y;
    cout << "Введите второе число";
    cin >> z;
    y = z - y;
    z = z - y;
    y = z + y;

    cout << "\n Первое число" << y << "\n Второе число" << z;
    
}


