#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> Find_Next(const string& needle)
{
    int length = needle.length();
    if(length == 1) return{-1};
    vector<int> next_vector(length);
    next_vector[0] = -1;//this makes sure that the iteration doesn't iterate forever
    next_vector[1] = 0;//for ther real substirng of a single letter is zero:needle[0...(1 - 0)]
    for(int i = 2; i < length; i++)//there is no need to calculate needle[length] since when you need it actually means you've already matched the needle
    {
        int k = next_vector[i - 1];
        while(k > - 1 && needle[i - 1] != needle[k])
        {
            k = next_vector[k];
        }
        next_vector[i] = k + 1;
    }
    return next_vector;

}

int Find(const string& haystack, const string& needle, const vector<int>& next)
{
    int h_length = haystack.length();
    int n_length = needle.length();
    int i = 0;
    int j = 0;
    while(i < h_length && j < n_length)
    {
        if(j == -1 || haystack[i] == needle[j])
        {
            j++;
            i++;
        }
        else
        {
            j = next[j];
        }
    }
    if(j == n_length)
    {
        return i - n_length;
    }
    return -1;
}
int main()
{
    string haystack;
    string needle;
    cin >> haystack >> needle;
    vector<int> next = Find_Next(needle);
    cout << Find(haystack, needle, next) << "\n";
    return 0;
}