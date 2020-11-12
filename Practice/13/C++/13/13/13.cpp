#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int a;
    cout << "Введите число" << endl;
    cin >> a;
    for (int i = 2; i <= sqrt(a) + 1; i++)
    {
        if (a % i == 0)
        {
            cout << "Составное";
            return 0;
        }
        else
            cout << "Простое";
        return 0;
    }
}

