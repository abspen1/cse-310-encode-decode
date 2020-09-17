/**
    CSE-310 P1: Take encoded input and output decoded input
    @file decode.cpp
    @author Austin Spencer
    @version Final 09/15/20
*/
#include <iostream>
#include <string>

using namespace std;

/**
    Sorts string array via insertion sort
    @param first pointer to the string array
    @param n number of strings in array
*/
void insertionSort(char *first, int n)
{
    int x, y;
    char key;
    for (x = 1; x < n; x++)
    {
        key = first[x];
        y = x - 1;
        while (y >= 0 && first[y] > key)
        {
            first[y + 1] = first[y];
            y = y - 1;
        }
        first[y + 1] = key;
    }
}

/**
    Swap helper function
    @param a pointer to the smaller string
    @param b pointer to the larger string
*/
void swap(string *a, string *b)
{
    string t = *a;
    *a = *b;
    *b = t;
}

/**
    Partition using last string as pivot
    @param str2 string array
    @param left smaller integer
    @param right larger integer
*/
int partition(string str2[], int left, int right)
{
    string pivot = str2[right]; // pivot
    int i = (left - 1);

    for (int j = left; j <= right - 1; j++)
    {
        // if current string is smaller than pivot, increment the left string
        if (str2[j] <= pivot)
        {
            i++; // increment index of smaller string
                 // swap strings at i and j
            swap(&str2[i], &str2[j]);
        }
    }
    // swap in pivot and return its position
    swap(&str2[i + 1], &str2[right]);
    return (i + 1);
}

/**
    Sorts given string array via quicksort
    @param str2 string array
    @param left starting index
    @param right largest index
*/
void quickSort(string str2[], int left, int right)
{
    if (left < right)
    {
        // partition the str2
        int pivot = partition(str2, left, right);

        // sort the sub str2 (divide & conquer)
        quickSort(str2, left, pivot - 1);
        quickSort(str2, pivot + 1, right);
    }
}

/**
    Formats our output and prints the encoded line with std::cout
    @param decode pointer to string of each final character of sorted string array
    @param n number of characters in string last
*/
void printDecodedLine(char *first, int *next, int sum, int index)
{
    string decodedString[sum];
    decodedString[0] = first[index];
    cout << decodedString[0];

    for (int i = 1; i < sum; i++)
    {
        index = next[index];
        decodedString[i] = first[index];
        cout << decodedString[i];
    }
}

bool numNotInNext(int num, int *next, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (num == next[i])
        {
            return false;
        }
    }
    return true;
}

/**
    The main function; reads input and calls other functions
    @param argc number of command line arguments
    @param argv array of each argument
*/
int main(int argc, char **argv)
{
    // Set variable keyword as the value of our second cmd line argument
    string keyword = argv[1];
    string str;
    bool flag = false;
    int index;
    int lines = 0;

    // While there is input in the txt file, set str equal to the current line
    while (getline(cin, str))
    {
        // If the line isn't empty, encode the line
        if (!str.empty())
        {
            // Increment number of lines, this will help us keep track of non-empty lines
            lines++;

            if (lines % 2 != 0)
            {
                index = stoi(str);
            }
            else
            {
                //Ignore new line for the first line
                if (lines != 2)
                {
                    cout << endl;
                }

                int n = str.size();

                char last[n];
                int charCount = 0;
                int j = 0;
                string bigNum;
                int num;
                int sum = 0;
               
                for (int i = 0; i < n; i++) {
                    if (j % 2 == 0) {
                        if (str[i+1] != ' ') {
                            bigNum = str[i];
                            int s = 1;
                            while (str[i + s] != ' ') {
                                bigNum = bigNum + str[i+s];
                                s++;
                            }
                            i += (s-1);
                            num = stoi(bigNum);
                            sum += num;
                        }else {
                            num = atoi(&str[i]);  // reset each time so we know how many letters
                            sum += atoi(&str[i]); // keeps track of total length of str array
                        }
                    }
                    else {
                        if(str[i] != ' '){
                            flag = true;
                        }
                        for (int k = 0; k < num; k++) {
                            // decompressing the string
                            last[charCount] = str[i];
                            charCount++;
                        }
                    }
                    i++; // second incrementer to skip over spaces
                    j++; // increment for just numbers and letters in string
                }

                if (!flag) {
                    for (int k = 0; k < num; k++)
                    {
                        cout << last[k];
                    }
                } else {
                    char first[sum]; // Initialize first char array
                    int next[sum];   // initialize next int array

                    for (int i = 0; i < sum; i++)
                    {
                        first[i] = last[i];
                        next[i] = -1; // reason for this numNotInNext was giving false positives
                    }
                    // Check keyword for which sorting algorithm to use
                    if (keyword == "quick")
                    {
                        // quickSort(first, 0, n - 1);
                        cout << "working on quick sort";
                        return 0;
                    }
                    else if (keyword == "insertion")
                    {
                        insertionSort(&first[0], sum); // Pass the address of our string array
                    }
                    else
                    {
                        cout << "invalid command line argument" << endl;
                        return -1; // return non-zero since an error occurred
                    }

                    char letter;
                    for (int i = 0; i < sum; i++)
                    {
                        letter = first[i];
                        for (int k = 0; k < sum; k++)
                        {
                            if (letter == last[k] && numNotInNext(k, &next[0], sum))
                            {
                                next[i] = k;
                                break;
                            }
                        }
                    }
                    printDecodedLine(&first[0], &next[0], sum, index);
                }
            }
        }
        else
        {
            // If the line is empty, print an empty line
            cout << endl;
        }
    }

    if (cin.bad())
    {
        cout << "IO error" << endl;
    }
    else if (!cin.eof())
    {
        cout << "format error" << endl;
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
} // End of program