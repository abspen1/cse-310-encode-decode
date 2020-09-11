#include <iostream>

using namespace std;

void iSort(int myarr[], int nElements)
{
    int x, key, y;
    for (x = 1; x < nElements; x++)
    {
        key = myarr[x];
        y = x - 1;
        while (y >= 0 && myarr[y] > key)
        {
            myarr[y + 1] = myarr[y];
            y = y - 1;
        }
        myarr[y + 1] = key;
    }
}

// Swap two elements - Utility function
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// partition the array using last element as pivot
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        //if current element is smaller than pivot, increment the low element
        //swap elements at i and j
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

//quicksort algorithm
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        //partition the array
        int pivot = partition(arr, low, high);

        //sort the sub arrays independently
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

//print our arrays
void printArray(int myArr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << myArr[i] << " ";
    cout << endl;
}

//main method
int main()
{
    int myarr[] = {141, 182, 194, 162, 171, 191, 135};
    int n = sizeof(myarr) / sizeof(myarr[0]);
    iSort(myarr, n);
    cout<<"Array sorted with insertion sort"<<endl;
    printArray(myarr, n);

    int arr[] = {12,23,3,43,51,35,19,45};
    int num = sizeof(arr)/sizeof(arr[0]);
    cout<<endl;
    quickSort(arr, 0, n-1);
    cout<<"Array sorted with quick sort"<<endl;
    printArray(arr,num);
    return 0;
}
