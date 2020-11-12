#pragma _2_H_
#define _2_H_

int Factorial(int n)
{
	return n <= 1 ? 1 : n * Factorial(n - 1);
}
