//手动指针遍历

#include <iostream>

#define MAXTOKEN 1005

using namespace std;

int search_word(char *s,char *target);

int main()
{
    int count = 0;
    cin >> count;


    cin.ignore(10000,'\n');
    //通过这种方式去除缓存区中的"\n"，避免第一次getline读到的是空字符串

    for(int i = 0;i < count;i++)
    {
        int w_count = 0;
        char s[MAXTOKEN];
        char target[15];
        cin.getline(s,MAXTOKEN);
        cin.getline(target,15);
        w_count = search_word(s,target);
        cout << "case #" << i << ":\n" << w_count << "\n";
    }
    return 0;
}
/*
我写的错误的search_word
int search_word(char *s,char *target)
{
    int word_count = 0;
    int i = 0,j = 0;
    while(s[i] != '\0')
    {
        while(s[i++] == target[j++])
        {
        }
        if(target[j] == '\0')
            word_count++;
        j = 0;
    }
    return word_count;
}
    */

int search_word(char *s,char *target)
{
    int word_count = 0,i = 0;
    while(s[i] != '\0')
    {
        while(s[i] == ' ')
            i++;
        if(s[i] == '\0')
            break;
        bool match = true;
        int j = 0;
        while(s[i] != ' ' && s[i] != '\0')
        {
            if(target[j] != '\0')
            {
                if(target[j] != s[i])
                    match = false;
                j++;
            }
            else
            {
                match = false;
            }
            i++;
        }
        if(match == true && target[j] == '\0')
        {
            word_count++;
        }
    }
    return word_count;
}