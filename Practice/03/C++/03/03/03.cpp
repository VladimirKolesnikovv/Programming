#include <iostream>
#include <locale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int a, b;
    cout << "Ввести первое число";
    cin >> a;
    cout << "Ввести второе число";
    cin >> b;
    cout << "\n Сумма равна" << a + b << "\n Разность равна" << a - b << "\n Произведение равно" << a * b << "\n Частное равно" << a / b << endl;
           
    double c, d;
    cout << "Введите первое число";
    cin >> c;
    cout << "Введите второе число";
    cin >> d;
    cout << "\n Сумма равна" << c + d << "\n Разность равна" << c - d << "\n Произведение равно" << c * d << "\n Частное равно" << c / d << endl;

    int e;
    double z;
    cout << "Ввести первое число";
    cin >> e;
    cout << "Ввести второе число";
    cin >> z;
    cout << "\n Сумма равна" << e + z << "\n Разность равна" << e - z << "\n Произведение равно" << e * z << "\n Частное равно" << e / z <<endl;

    double y;
    int g;
    cout << "Ввести первое число";
    cin >> y;
    cout << "Ввести второе число";
    cin >> g;
    cout << "\n Сумма равна" << y + g << "\n Разность равна" << y - g << "\n Произведение равно" << y * g << "\n Частное равно" << y / g <<endl;
}


