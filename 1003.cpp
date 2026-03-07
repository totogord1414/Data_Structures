#include <iostream>
#include <string>
#include <map>

using namespace std;

char get_digit(char c)
{
    if(c >= '0' && c <= '9') return c;
    if(c >= 'A' && c <= 'C') return '2';
    if(c >= 'D' && c <= 'F') return '3';
    if(c >= 'G' && c <= 'I') return '4';
    if(c >= 'J' && c <= 'L') return '5';
    if(c >= 'M' && c <= 'O') return '6';
    if(c >= 'P' && c <= 'S') return '7';
    if(c >= 'T' && c <= 'V') return '8';
    if(c >= 'W' && c <= 'Z') return '9';
    return '?';
}

int main()
{
    int T;
    if(!(cin >> T))
        return 0;
    map<string , int> dionumber;//map的实际类型是const &pair
    for(int i = 0;i < T;i++)
    {
        string rawStr;
        cin >> rawStr;
        string cleanStr = "";
        for(int j = 0;j < rawStr.size();j++)//容器都尽量用size，不要使用strlen
        {
            if(rawStr[j] == '-')
                continue;
            cleanStr += get_digit(rawStr[j]);
        }
        cleanStr = cleanStr.substr(0,4) + "-" + cleanStr.substr(4);
        dionumber[cleanStr]++; 
    }
    for(const auto& pair : dionumber)
    {
        cout << pair.first << " " << pair.second << endl;
    }
    return 0;
}