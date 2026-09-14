#include <iostream>
#include <stdarg.h>
#include <cmath>
#include <stdlib.h>
void insert_heap(int *heap, int position)
{
    std::cout << "Inserting value: " << heap[position] << std::endl;
    int temp = heap[position], i = position;

    while (i > 0 && (temp > heap[i / 2]))
    {
        heap[i] = heap[i / 2]; // child gets the value of the parent
        i = i / 2;
    }
    heap[i] = temp; // then the final parent is updated
}
void create_heap(int *heap, int size)
{

    for (int i = 1; i < size; i++)
    // insert_heap()
    {
        insert_heap(heap, i);
    }
}
void print_array(int *heap, int size)
{
    std::cout << "Size: " << size << ", The heap is:" << std::endl;

    for (int i = 0; i < size; i++)
    {
        std::cout << i << ") " << heap[i] << " " << std::endl;
    }

    return;
}
void levelWisePrinting(int *heap, int size)
{

    std::cout << "Size: " << size << ", The level wize heap is:" << std::endl;
    for (int i = 0; i < 1; i++)
    {

        std::cout << heap[i] << std::endl;
        std::cout << "/" << " " << "\\" << std::endl;
        if (2 * i < size)
            std::cout << heap[2 * i];
        if ((2 * i + 1) < size)
            std::cout << heap[2 * i + 1];
    }
}
int main()
{
    int array_heap[] = {1, 5, 34, 1, 4, 8, 9, 7, 4, 5};
    int array_heap2[] = {1, 5};
    print_array(array_heap2, sizeof(array_heap2) / sizeof(int));
    // levelWisePrinting(array_heap2, sizeof(array_heap2) / sizeof(int));
    create_heap(array_heap2, sizeof(array_heap2) / sizeof(int));
    print_array(array_heap2, sizeof(array_heap2) / sizeof(int));
    return 0;
}
