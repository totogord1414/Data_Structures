#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int cmp(const vector<int>& A,const vector<int>& B,int m,int n)
{
    int min_len = min(m,n);

    for(int i = 0;i < min_len;i++)
    {
        if(A[i] < B[i])
            return -1;
        if(A[i] > B[i])
            return 1;
    }
    if(m == n)
        return 0;
    if(m > n)
        return 1;
    if(m < n)
        return -1;
}

int main()
{
    int m,n;
    cin >> m >> n;
    vector<int> A(m);
    vector<int> B(n);
    for(int i = 0;i < m;i++)
        cin >> A[i];
    for(int i = 0; i < n;i++)
        cin >> B[i];
    cout << cmp(A,B,m,n);   
}