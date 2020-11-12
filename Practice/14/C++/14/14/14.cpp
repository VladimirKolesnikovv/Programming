#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
	int  n, a, b;
	double c, x;
	cout << "Введите число" << endl;
	cin >> n;
	x = 0;
	c = 0;
	b = 0;
	for (a = 1; a <= n; a++) {
		c = pow(2, x);
		if ((x <= n) && (c <= n)) {
			b++;
		}
		else {
			n = x;

		}
		x++;
	}
	cout << b;
}

