#include <iostream>
#include <string>
using namespace std;

int main()
{
    string haystack;
    string needle;
    cin >> haystack >> needle;
    size_t pos = haystack.find(needle);
    if(pos == string::npos)
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << pos << "\n";
    }
    return 0;
}