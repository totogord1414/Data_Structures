#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Compare{
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

int solve(vector<int> num)
{
    int result = 0;
    priority_queue<int, vector<int>, Compare> pq;
    for(int x:num)
    {
        pq.push(x);
    }
    for(int i = 0; i < num.size() - 1; i++)
    {
        int left = pq.top();
        pq.pop();
        int right = pq.top();
        pq.pop();
        result += left + right;
        pq.push(left + right);
    }
    result += pq.top();
    return result;
}


int main()
{
    int n;
    cin >> n;
    vector<int> num(n);
    for(int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    cout << solve(num) << endl;
}