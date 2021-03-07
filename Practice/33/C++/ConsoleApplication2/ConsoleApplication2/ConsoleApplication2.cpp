#include <iostream>
#include <string>
#include <cmath>
#include <locale>


int *create(int const size, const int start, const int step)
{
	int* ptrarr = new int[size];
	*ptrarr = start;
	for (int i = 1; i < size; i++)
	{
		*(ptrarr+i) = *(ptrarr+i-1)  + step;
	}
	return ptrarr;
}

void sort(int* ptr_ptrarr, const int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0 && ptr_ptrarr[j - 1] > ptr_ptrarr[j]; j--)
		{
			int temp = *(ptr_ptrarr+j-1);
			*(ptr_ptrarr+j-1) = *(ptr_ptrarr+j);
			*(ptr_ptrarr + j) = temp;
		}
	}
}

void print(int *ptr_ptrarr, const int size)
{
	std::cout << "[";
	for (int i = 0; i < size; i++)
	{
		if (i<size-1) 
		{
			std::cout << *(ptr_ptrarr + i) << " ";
		}
		else
		{
			std::cout << *(ptr_ptrarr + i);
		}
	}
	std::cout << "]";
}


int main(int argc, const char * argv[])
{
	setlocale(LC_ALL,"ru");

	int size, step = 0, start = 0;

	std::cout << "Введите размер начало и шаг арифметической прогрессии" << std::endl;
	std::cin >> size >> start >> step;

	int* ptr_ptrarr = create(size, start, step);

	create(size,start, step);
	sort(ptr_ptrarr, size);
	print(ptr_ptrarr, size);
	delete[]ptr_ptrarr;
	std::cin.get();
	return 0;
}
