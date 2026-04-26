#include<iostream>

const int MAXN = 1e4 + 5;
int node[MAXN];
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int num;
    cin >> num;
    for(int k = 1; k <= num; k++)
    {
        cin >> node[k];
    }
    int i, j;
    cin >> i >> j;
    if(i > num || node[i] == 0)
    {
        cout << "ERROR: T[" << i << "] is NULL" << endl;
        return 0;
    }
    if(j > num || node[j] == 0)
    {
        cout << "ERROR: T[" << j << "] is NULL" << endl;
        return 0;
    }
    while(i != j)
    {
        if(i > j)
            i = i / 2;
        else
            j = j / 2;
    }
    cout << i << " "<< node[i];
    return 0;
}