#include <iostream>
#include <clocale>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int a, b, c, z;
		a = 2;
	    b = 2;
		c = 2;
		z = a + b * c;
		cout << "Результат выражения 2+2*2 = " << z;
		return 0;

}
