#include <iostream>
#include <string>
#include <sstream>  //引入字符串流，处理按空格分割单词

using namespace std;

int main()
{
    int T;
    if(!(cin >> T))
        return 0;
    string dummy;
    getline(cin,dummy);
    for(int i = 0;i < T;i++)
    {
        string s;
        string t;
        getline(cin,s);
        getline(cin,t);
        stringstream ss(s);//把字符串s塞入字符串流中

        string word;
        int count = 0;
        while(ss >> word)
        {
            if(word == t)
                count++;
        }

        cout << "case #" << i << ":" << endl;
        cout << count << endl;
    }
    return 0;
}