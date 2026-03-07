#include <string>

void itob(int n,std::string& s,int b)
{
    // TODO: your function definition
    bool sign  = true;
    s = "";
    if(n  == 0)
        s = "0";//不能忘记边界情况！！
    if(n < 0)
    {
        n = -n;
        sign  = false;
    }
    while(n)
    {
        int i = n % b;
        char c = i < 10 ? i + '0' : i - 10 + 'A';
        s = c + s;//这样的作法会导致内存一直搬家，更好的做法是+= 再reserve
        n /= b;
    }
    if(!sign)
        s = '-'  + s;
}

#include <algorithm>

void itob(int n,std::string& s,int b)
{
    bool is_negative = false;
    if(n == 0)
    {
        s = '0';
        return;
    }

    long long num = n;//防止最大负数转换的时候会溢出
    if(num < 0)
    {
        num = -num;
        is_negative = true;
    }
    while(num > 0)
    {
        int i = num % b;
        char c = i < 10 ? i + '0' : i - 10 + 'A';

        s += c;
        num /= b;
    }
    if(is_negative)
        s += '-';
    std::reverse(s.begin(),s.end());
}
