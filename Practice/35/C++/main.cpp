#include <iostream>


struct IntArray {
  int *data;
  int size;
};
void create(IntArray& arr, int size)
{
    if (size <= 0)
    {
        std::cout << "you have gone beyond the boundaries of the array\n";
    }
    arr.data = new int[size];
    if (arr.data == 0)
    {
        std::cout << "it is not possible to create an array with this size\n";
    }
    arr.size = size;
}
void create(IntArray* arr, int size)
{
    create(*arr, size);
}

int get(IntArray& arr, int index)
{
    if (index < 0 || index >= arr.size)
    {
        std::cout<<"you are out of the array\n";
        exit(1);
    }
    return arr.data[index];
}
int get(IntArray* arr, int index)
{
    return get(*arr, index);
}

void set(IntArray& arr, int index, int value)
{
    if (index < 0 || index >= arr.size)
    {
        std::cout << "index out of range";
        exit(1);
    }
    arr.data[index] = value;
}
void set(IntArray* arr, int index, int value)
{
    set(*arr, index, value);
}

void resize(IntArray& arr, int newSize)
{
    if (newSize <= 0)
    {
        return;
    }

    if (newSize == arr.size)
    {
        return;
    }
    else if (newSize > arr.size)
    {
        int *newArray = new int[newSize];
        if (!newArray)
        {
            std::cout<<"Can't create";
            return;
        }
        memcpy(newArray, arr.data, sizeof(int)*arr.size);
        //to copy a memory area
        for (int i = arr.size; i < newSize; ++i)
            newArray[i] = 0;

        // delete old data with new array
        delete[] arr.data;
        arr.data = newArray;
        arr.size = newSize;
    }
    else
    {
        int *newArray = new int[newSize];
        if (!newArray)
        {
            std::cout<<"it is not possible to create an array with this size\n";
            return;
        }
        memcpy(newArray, arr.data, sizeof(int)*newSize);
        delete[] arr.data;
        arr.data = newArray;
        arr.size = newSize;
    }
}
void resize(IntArray* arr, int newSize)
{
    resize(*arr, newSize);
}

void destroy(IntArray& arr)
{
    if (!arr.data)
    {
        delete[] arr.data;
        arr.data = nullptr;
    }
    arr.size = 0;
}
void destroy(IntArray* arr)
{
    destroy(*arr);
}

void print(IntArray& arr)
{
    if (arr.size == 0)
    {
        puts("[]");
        return;
    }
    if (arr.size < 0)
    {
        return;
    }
    std::cout << "[";
        for (int i = 0; i < arr.size; i++)
        {
            if (i < arr.size - 1)
            {
                std::cout << *(arr.data + i) << " ";
            }
            else
            {
                std::cout << *(arr.data + i);
            }
        }
        std::cout << "]\n";
}
void print(IntArray* arr)
{
    print(*arr);
}
int main()
{
    {
        int size = 30;
        IntArray arr;

        create(arr, size);
        for (int i = 0; i < size; ++i)
            set(arr, i, i+1);
        print(arr);

        resize(arr, 50);
        print(arr);

        resize(arr, 10);
        print(arr);

        destroy(arr);
    }

    std::cin.get();
    return 0;
}
