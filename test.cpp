#include <iostream>

using namespace std;

void insertionSort(string* str2, int n)
{
    int x, y;
    string key;
    for (x = 1; x < n; x++)
    {
        key = str2[x];
        y = x - 1;
        while (y >= 0 && str2[y] > key)
        {
            str2[y + 1] = str2[y];
            y = y - 1;
        }
        str2[y + 1] = key;
    }
}

// Swap two elements - Utility function
void swap(string *a, string *b)
{
    string t = *a;
    *a = *b;
    *b = t;
}

// partition the str2ay using last element as pivot
int partition(string str2[], int low, int high)
{
    string pivot = str2[high]; // pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        //if current element is smaller than pivot, increment the low element
        //swap elements at i and j
        if (str2[j] <= pivot)
        {
            i++; // increment index of smaller element
            swap(&str2[i], &str2[j]);
        }
    }
    swap(&str2[i + 1], &str2[high]);
    return (i + 1);
}

//quicksort algorithm
void quickSort(string str2[], int low, int high)
{
    if (low < high)
    {
        //partition the str2
        int pivot = partition(str2, low, high);

        //sort the sub str2 independently
        quickSort(str2, low, pivot - 1);
        quickSort(str2, pivot + 1, high);
    }
}

// shift our string by taking substring that doesn't include first char, then add first char to end
void shift(string s){s = s.substr(1, 25) + s.substr(0, 1);}

void printChar(const string &s)
{
    for (string::size_type i = 0; i < s.size(); i++)
    {
        cout << s[i] << ' ';
    }
    cout << endl;
}

void doStuff(string& str, int n)
{
    string *str2 = new string[n];
    string original;
    str2[0] = str;
    original = str;

    // cout << "input shifted 0: " << str << endl;
    for (string::size_type i = 1; i < (n); i++)
    {
        str = str.substr(1, 25) + str.substr(0, 1);
        // cout << "input shifted " << i << ": " << str << endl;
        str2[i] = str;
    }
    
    // Pass the address of the string array at index 0
    insertionSort(&str2[0], n);

    // quickSort(str2, 0, n-1);

    int originalLocation;
    string last[n];

    for (int i = 0; i < n; ++i)
    {
        // cout << "lexicographical sort " << i << ": " << str2[i] << endl;
        last[i] = str2[i].back();
        if (str2[i].compare(original) == 0)
        {
            originalLocation = i;
        }
    }
    cout << originalLocation << endl;

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
    cout << endl;
}

//main method
int main()
{
    string str;
    str = "Mississippi";
    int lines = 0;
    doStuff(str, str.size());

    return 0;
}