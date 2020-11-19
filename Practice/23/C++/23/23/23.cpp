#include <iostream> 
#include <iomanip> 
#include <cmath>
#include <locale>
#include "Factorial.h" 
#include "Sin.h" 
#include "Soch.h" 

using namespace std;

int main() {
	cout << "n" << "\t" << "n!\n";
	for (int n = 1; n <= 10; n++) {
		cout << n << "\t" << Fac(n) << "\n";
	}
	cout << "\n";

	float p = 3.1415;
	cout << "x" << "\t" << "sin(x)\n";
	for (float x = 0; x <= p / 4; x = x + p / 180) {
		cout << x << "\t" << setprecision(4) << Sin(x) << "\n";
	}
	cout << "\n";

	int n = 10;
	cout << "k" << "\t" << "c(k, 10)\n";
	for (int k = 1; k <= n; k++) {
		cout << k << "\t" << Soch(k, n) << "\n";
	}
}
