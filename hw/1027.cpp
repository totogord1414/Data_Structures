#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int find_lps(const string& needle)
{
    int length = needle.length();
    if(length == 0) return 0;
    vector<int> next(length);
    int i = 0, j = 0;//i points to the tail of the current suffix,j points to the tail of the current prefix
    next[0] = 0;//it means the lengths of the substring is 0
    for(i = 1;i < length;i++)
    {
        while(j > 0 && needle[i] != needle[j])//if the next doesn't match
        {
            j = next[j - 1];
        }
        if(needle[i] == needle[j])//if the next matches
        {
            j++;
        }
        next[i] = j;
    }
    return next[length - 1];
}
int main()
{
    int word_num;
    cin >> word_num;
    string haystack;
    for(int i = 0;i < word_num; i++)
    {
        string needle;
        cin >> needle;
        int tail_len = min(needle.length(), haystack.length());
        string temp_needle = needle + "#" + haystack.substr(haystack.length() - tail_len, tail_len);
        int bonus = find_lps(temp_needle);
        needle.erase(0, bonus);
        haystack += needle;
    }
    cout << haystack << "\n";
    return 0;
}