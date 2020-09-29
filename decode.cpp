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
    Sorts char array via insertion sort
    @param first pointer to the char array
    @param n number of chars in array
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
    @param a pointer to the smaller char array
    @param b pointer to the larger char array
*/
void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

/**
    Partition using last char as pivot
    @param first char array
    @param left smaller integer
    @param right larger integer
*/
int partition(char* first, int left, int right)
{
    char pivot = first[right]; // pivot
    int i = (left - 1);

    for (int j = left; j <= right - 1; j++)
    {
        // if current char array is smaller than pivot, increment the left char array
        if (first[j] <= pivot)
        {
            i++; // increment index of smaller char array
                 // swap strings at i and j
            swap(&first[i], &first[j]);
        }
    }
    // swap in pivot and return its position
    swap(&first[i + 1], &first[right]);
    return (i + 1);
}

/**
    Sorts given char array via quicksort
    @param first char array
    @param left starting index
    @param right largest index
*/
void quickSort(char* first, int left, int right)
{
    if (left < right)
    {
        // partition the first
        int pivot = partition(first, left, right);

        // sort the sub first (divide & conquer)
        quickSort(first, left, pivot - 1);
        quickSort(first, pivot + 1, right);
    }
}

/**
    Formats our output and prints the decoded line with std::cout
    @param first    pointer to char array
    @param next     pointer to our int array
    @param sum      (int) total number of characters in array
    @param index    (int) index where our original string begins
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

/**
    Helper function that makes sure we don't append the same index twice to 
    our int array 'next'
    @param num  (int) total number of characters in array
    @param next pointer to our int array
    @param n    (int) index where our original string begins
*/
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

                for (int i = 0; i < n; i++)
                {
                    if (j % 2 == 0)
                    {
                        if (str[i + 1] != ' ')
                        {
                            bigNum = str[i];
                            int s = 1;
                            while (str[i + s] != ' ')
                            {
                                bigNum = bigNum + str[i + s];
                                s++;
                            }
                            i += (s - 1);
                            num = stoi(bigNum);
                            sum += num;
                        }
                        else
                        {
                            num = atoi(&str[i]);  // reset each time so we know how many letters
                            sum += atoi(&str[i]); // keeps track of total length of str array
                        }
                    }
                    else
                    {
                        for (int k = 0; k < num; k++)
                        {
                            // decompressing the string
                            last[charCount] = str[i];
                            charCount++;
                        }
                    }
                    i++; // second incrementer to skip over spaces
                    j++; // increment for just numbers and letters in string
                }

                char first[sum]; // Initialize first char array
                int next[sum];   // initialize next int array

                for (int i = 0; i < sum; i++)
                {
                    first[i] = last[i];
                    next[i] = -1; // reason for this, numNotInNext was giving false positives
                }
                // Check keyword for which sorting algorithm to use
                if (keyword == "quick")
                {
                    quickSort(&first[0], 0, sum - 1);
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