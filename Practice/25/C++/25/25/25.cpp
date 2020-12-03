#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
	const int length = 4;
	int array[length] = { 2, 1, 7, -3 };

	std::sort(array, array + length);

	for (int i = 0; i < length; ++i)
		std::cout << array[i] << ' ';

	return 0;
}
