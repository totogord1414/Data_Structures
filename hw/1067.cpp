#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        pq.push(temp);
    }
    int bonus = (k - 1) - ((n - 1) % (k - 1));
    for(int j = 0; j < bonus; j++)
    {
        pq.push(0);
    }

    long long result = 0;

    while(pq.size() > 1)
    {
        long long value = 0;
        for(int i = 0; i < k; i++)
        {
            value += pq.top();
            pq.pop();
        }
        result += value;
        pq.push(value);
    }
    cout << result << "\n";
}