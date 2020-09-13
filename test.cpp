#include <iostream>

using namespace std;

void shift(string &s)
{
    reverse(s.begin(), s.begin() + 1);
    reverse(s.begin() + 1, s.end());
    reverse(s.begin(), s.end());
}

void printChar(const string &s)
{
    for (string::size_type i = 0; i < s.size(); i++)
    {
        cout << s[i] << ' ';
    }
    cout << endl;
}

void doStuff(string &str, int lines)
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

    // cout << "input shifted 0: " << str << endl;
    for (string::size_type i = 1; i < (n); i++)
    {
        shift(str);
        // cout << "input shifted " << i << ": " << str << endl;
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
    str = "End of Project Gutenberg Etext of Anne of Avonlea.";
    int lines = 0;
    doStuff(str, lines);

    return 0;
}