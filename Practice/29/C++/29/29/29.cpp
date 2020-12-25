#include "iostream"
#include <string.h>
#include <stdlib.h>

using namespace std;

#define N 10

struct STUDENT
{
    char name[30];
    int group;
    int ses[5];
};

int cmp(const void* p1, const void* p2)
{
    return strcmp(((STUDENT*)p1)->name, ((STUDENT*)p2)->name);
}

int main()
{
    STUDENT stud1[N];

    for (int st = 0; st < N; st++)
    {
        cout << "Input first name: ";
        cin.getline(stud1[st].name, 30);
        cout << "Input number of group: ";
        cin >> stud1[st].group;

        for (int i = 0; i < 5; i++)
        {
            cout << "Input mark " << i + 1 << ": ";
            cin >> stud1[st].ses[i];
        }

        cout << endl;
        cin.get();
    }

    qsort(stud1, N, sizeof(STUDENT), cmp);

    int fl = 1;
    for (int i = 0; i < N; i++)
    {
        int j = 0;
        while ((j < 5) && (stud1[i].ses[j] != 2))
            j++;
        if (j < 5)
        {
            fl = 0;
            cout << "Student " << stud1[i].name << " (group " << stud1[i].group << ") have mark 2" << endl;
        }
    }
    if (fl)
        cout << "No students, which have mark 2" << endl;

    cin.get();
    return 0;
}