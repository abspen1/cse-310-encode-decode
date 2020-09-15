
#include <stdio.h>

void print_array(int *data, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", *data);
        data++;
    }
    printf("\n");
}

void shift_element(int *arr, int *i)
{
    int ival;
    for (ival = *i; i > arr && *(i - 1) > ival; i--)
    {
        *i = *(i - 1);
    }
    *i = ival;
}

void insertion_sort(int *arr, int len)
{
    int *i, *last = arr + len;
    for (i = arr + 1; i < last; i++)
        if (*i < *(i - 1))
            shift_element(arr, i);
}

int main()
{

    int arr[5] = {99, 78, -1, 42, 12};
    int n = sizeof(arr) / sizeof(int);

    print_array(&arr[0], n);

    insertion_sort(&arr[0], n);

    print_array(&arr[0], n);
    return 0;
}