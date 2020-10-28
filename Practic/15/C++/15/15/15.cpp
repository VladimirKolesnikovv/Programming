#include <iostream>
#include <ctime>
#include <locale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int a, b, c, h, f, o;
    a = 1;
    c = 5;
    o = 0;
    cout << "Компьютер загадал число от 0 до 100, попробуйте его отгадать" << endl;
    for (int i = 1; i <= c; i++) {
        if ((a == 1) || (a == 0)) {
            srand(time(0));
            b = 1 + rand() % 100;
        }
        cout << "Введите число" << endl;
        if (a == 5) {
            cin >> h;
            cout << endl;
            if (h == b) {
                cout << "Поздравляю!Вы угадали" << endl << "Хотите начать сначала?(1-Да)" << endl;
                cin >> f;
                if (f == 1) {
                    c = c * 2;
                    a = 0;
                }

            }
            else {
                cout << "Вы проиграли. Было загадано:" << b << endl << "Хотите начать сначала?(1-Да)" << endl;
                cin >> f;
                if (f == 1) {
                    c = (c * 2) + 1;
                    a = 0;
                }


            }

        }
        else {
            cin >> h;
            cout << endl;
            o++;
            if (h == b) {
                cout << "Поздравляю!Вы угадали" << endl << "Хотите начать сначала?(1-Да)" << endl;
                cin >> f;
                if (f == 1) {
                    c = o + 5;
                    a = 0;
                }

            }
            else {
                if (h > b) {
                    cout << "Число меньше" << endl;


                }
                else {
                    cout << "Число больше" << endl;
                }

            }

        }
        a++;
    }
}


