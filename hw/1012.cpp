#include <iostream>
#include <string>


using namespace std;

int main()
{
    int guess = 0;
    int min = -1e9;
    int max = 1e9;
    cout << guess << endl;
    string result;
    while(cin >> result)
    {
        if(result == "equal")
            return 0;
        else if(result == "small")
        {            
            min = guess + 1;
            guess = (min + max) / 2;
        }
        else
        {
            max = guess - 1;
            guess = (min + max) / 2;
        }
        cout << guess << endl;
    }
}