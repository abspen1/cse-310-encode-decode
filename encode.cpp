#include <iostream>
#include <string>
#include <string.h>

using namespace std;

// Global variable declaration:
int sort_algorithm = 0;

/**
shift given string: 
Take substring(not including first char)
Take substring of only first char and add it to the end of first substring
*/
void shift(string &s) { s = s.substr(1, 25) + s.substr(0, 1); }

// insertion sort
void insertionSort(string str2[], int n)
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

// swap two strings
void swap(string *a, string *b)
{
    string t = *a;
    *a = *b;
    *b = t;
}

// partition str2 using last string as pivot
int partition(string str2[], int left, int right)
{
    string pivot = str2[right]; // pivot
    int i = (left - 1);

    for (int j = left; j <= right - 1; j++)
    {
        //if current string is smaller than pivot, increment the left string
        //swap strings at i and j
        if (str2[j] <= pivot)
        {
            i++; // increment index of smaller string
            swap(&str2[i], &str2[j]);
        }
    }
    // swap in pivot and return its position
    swap(&str2[i + 1], &str2[right]);
    return (i + 1);
}

//quicksort algorithm
void quickSort(string str2[], int left, int right)
{
    if (left < right)
    {
        //partition the str2
        int pivot = partition(str2, left, right);

        //sort the sub str2 independently
        quickSort(str2, left, pivot - 1);
        quickSort(str2, pivot + 1, right);
    }
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

void encode(string &str, int lines)
{
    // cout << "input: " << str << endl;
    if (lines != 0)
    {
        cout << endl;
    }
    int n = str.size();

    string* str2 = new string[n];
    string original;
    str2[0] = str;
    original = str;

    for (string::size_type i = 1; i < (n); i++)
    {
        shift(str);
        str2[i] = str;
    }

    // If the comparison is == 0 then run quick sort since our argument was "quick"
    if (sort_algorithm == 0){
        quickSort(str2, 0, n - 1);
    } else // Run insertion is sort_algorithm does not equal 0
    {
        insertionSort(str2, n);
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

int main(int argc, char** argv)
{
    const char *quick = "quick";
    // Set global variable = to the comparison of our second argument and "quick"
    sort_algorithm = strcmp(argv[1], quick);

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