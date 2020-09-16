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
void insertionSort(char* first, int n)
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
void printDecodedLine(char* decode, int n)
{
    for(int i = 0; i < n; i++){
        cout << decode[i];
    }
}

bool numNotInNext(int num, int* next, int n) {
    for(int i = 0; i < n; i++) {
        if (num == next[i]){
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
    int
    main(int argc, char **argv)
{
    // Set variable keyword as the value of our second cmd line argument
    string keyword = argv[1];
    string str;
    int decodeIndex;
    int lines = 0;

    // While there is input in the txt file, set str equal to the current line
    while (getline(cin, str))
    {
        // If the line isn't empty, encode the line
        if (!str.empty())
        {
            // Increment number of lines, this will allow to skip first line and add EOL to the rest
            lines++;
            
            if (lines % 2 != 0){
                decodeIndex = stoi(str);
                // cout << decodeIndex;
            }else
            {
                int n = str.size();

                // cout << str;
                // Initialize str2 (string array we will be sorting)
                char last[n];
                int charCount = 0;
                int j = 0;
                int num;
                int sum = 0;

                for (int i = 0; i < n; i++)
                {
                    if (j % 2 == 0) {                        
                        num = atoi(&str[i]); // reset each time so we know how many letters
                        sum += atoi(&str[i]); // keeps track of total length of str array
                    }
                    else {
                        for (int k = 0; k < num; k++){
                            last[charCount] = str[i];
                            charCount++;
                        }
                    }
                    i++; // second incrementer to skip over spaces
                    j++; // increment for just numbers and letters in string
                }

                char first[sum]; // Initialize first char array
                for (int i =0; i < sum; i++) {
                    first[i] = last[i];
                }
                insertionSort(&first[0], sum); // Pass the address of our string array

                // Now that I have first and last strings.. need to calculate Next
                int next[sum]; // initialize next int array
                // initialize the indexes to -1
                for (int i = 0; i < sum; i++) {
                    next[i] = -1;   
                }
                char letter;
                for (int i = 0; i < sum; i++) {
                    letter = first[i];
                    for (int k = 0; k < sum; k++) {
                        if (letter == last[k] && numNotInNext(k, &next[0], sum))
                        {
                            // cout << letter << " = " << last[k] << " index: " << k << endl;
                            next[i] = k;
                            break;
                        }
                    }
                }
                for (int i = 0; i < sum; i++) {
                    cout << next[i] << " ";
                }
            }
            
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