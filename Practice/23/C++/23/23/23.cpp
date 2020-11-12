#include <iostream>
#include<locale>
#include<iomanip>
#include "file1.h"

using namespace std;

int main()
{
	cout << "n" << setw (8) << "!n"<<endl;
	cout << 1 << setw(8) << Factorial(1) << endl;
	cout << 2 << setw(8) << Factorial(2) << endl;
	cout << 3 << setw(8) << Factorial(3) << endl;
	cout << 4 << setw(9) << Factorial(4) << endl;
	cout << 5 << setw(10) << Factorial(5) << endl;
	cout << 6 << setw(10) << Factorial(6) << endl;
	cout << 7 << setw(11) << Factorial(7) << endl;
	cout << 8 << setw(12) << Factorial(8) << endl;
	cout << 9 << setw(13) << Factorial(9) << endl;
	cout << 10 << setw(13) << Factorial(10) << endl;
}

