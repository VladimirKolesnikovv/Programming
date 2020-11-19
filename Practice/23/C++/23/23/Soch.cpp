#include <cmath>
#include "Soch.h" 
#include "Factorial.h" 

int Soch(int k, int n)
{
	int c = 0;
	c = Fac(n) / (Fac(k) * Fac(n - k));
	return c;
}