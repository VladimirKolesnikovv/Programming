#include <iostream>
#include <string>
using namespace std;
int main() {
    setlocale(LC_ALL, "rus");
    struct student {
        string fio;
        int group;
        int scor[5];
    };
    cout << "Введите количество студентов" << endl;
    int n;
    cin >> n;
    student* st = new student[n];
    for (int i = 0; i != n; i++) {
        cout << "Введите ФИО" << endl;
        cin >> st[i].fio;
        cout << "Введите номер группы" << endl;
        cin >> st[i].group;
        cout << "Успеваемость" << endl;
        int j = 0;
        do {
            cout << "Оценка" << endl;
            cin >> st[i].scor[j];
            j++;
        } while (j != 5);
        cout << endl;
    }
    cout << endl;
    // сортируем по возрастанию групп
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i; i++)
            if (st[j].group > st[j + 1].group)
                swap(st[j].group, st[j + 1].group);
    // выводим студентов по возрастанию групп
    for (int i = 0; i != n; i++) {

        cout << st[i].fio << endl;
        cout << st[i].group << endl;
        for (int j = 0; j != 5; j++) {
            cout << st[i].scor[j] << " ";
        }
        cout << endl;

    }
    cout << endl;
    int sum = 0;
    int ind;
    int f = 0;
    cout << "Студенты средний бал >4" << endl;
    for (int i = 0; i != n; i++)
        if (((st[i].scor[0] + st[i].scor[1] + st[i].scor[2] + st[i].scor[3] + st[i].scor[4]) / 5) > 4) {
            f++;
            ind = i;
        }
    if (f > 0) {
        cout << st[ind].fio << endl;
        cout << st[ind].group << endl;
    }
    else cout << "Таких нет" << endl;

    system("pause");
    return 0;
}
