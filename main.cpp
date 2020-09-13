#include <iostream>

using namespace std;

void insertionSort(int myarr[], int nElements)
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

// shift function that will shift our string by 1 each time it is called
void shift(string & s)
{
    reverse(s.begin(), s.begin() + 1);
    reverse(s.begin() + 1, s.end());
    reverse(s.begin(), s.end());
}

void printEncodedLine(string last[], int n)
{
    int num = 1;

    for (int i = 0; i < n; i++)
    {
        if (last[i] == last[i + 1])
        {
            num++;
            continue;
        }
        cout << num << " " << last[i];
        if (i != n)
        {
            cout << " ";
        }
        num = 1;
    }
}

void encode(string & str, int lines)
{
    // cout << "input: " << str << endl;
    if (lines != 0)
    {
        cout << endl;
    }
    int n = str.size();

    string str2[n], temp, original;
    str2[0] = str;
    original = str;

    for (string::size_type i = 1; i < (n); i++)
    {
        // shift our string by 1
        shift(str);
        // append our str2 string array with each shift of str
        str2[i] = str;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (str2[i] > str2[j])
            {
                temp = str2[i];
                str2[i] = str2[j];
                str2[j] = temp;
            }
        }
    }

    int originalLocation;
    string last[n];

    for (int i = 0; i < n; ++i)
    {
        // append our string last with the final character in str2
        last[i] = str2[i].back();
        // check if the current str2 is our original string
        if (str2[i].compare(original) == 0)
        {
            // If it is our original string set originalLocation equal to the index we are at
            originalLocation = i;
        }
    }
    // Print the index of our original string
    cout << originalLocation << endl;
    printEncodedLine(last, n);
}

//main method
int main()
{
    string str;
    int lines = 0;

    // While there is input in the txt file, set str equal to the current line
    while (getline(cin, str))
    {
        // If the line isn't empty, encode the line
        if (!str.empty())
        {
            encode(str, lines);
        }
        else
        {
            // If the line is empty, print an empty line
            cout << endl;
        }
        // Increment number of lines, this is used to tell the encoding function to print an EOL
        lines++;
    }

    if (cin.bad())
    {
        cout << "IO error" << endl;
        // IO error
    }
    else if (!cin.eof())
    {
        cout << "format error" << endl;
        // format error
    }
    else
    {
        if (str.empty())
        {
            // Add empty line if file ends with an empty line
            cout << endl;
        }
        // end of file
    }

    return 0;
}
