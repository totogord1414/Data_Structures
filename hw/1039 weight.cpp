#include <bits/stdc++.h>

using namespace std;

class UnionFind 
{
private:
    vector<int> weight;
    vector<int> parent;

    int Find(int n)
    {
        if(parent[n] != n)
        {
            int temp = parent[n];
            parent[n] = Find(parent[n]);
            weight[n] += weight[temp];
        }
        return parent[n];
    }

    void Union(int m, int n)
    {
        int x = Find(m);
        int y = Find(n);
        if(x == y)  return;
        parent[y] = x;
        weight[y] = weight[m] - weight[n] - 1;
    }
public:
    UnionFind (int n)
    {
        parent.resize(n);
        weight.resize(n, 0);
        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    void read_command(char c, int m, int n)
    {
        if(c == 'A')
        {
            Union(m, n);
        }
        else if(c == 'Q')
        {
            int x = Find(m);
            int y = Find(n);
            if(x != y)
            {
                cout << "Not sure yet.\n";
            }
            else
            {
                if((weight[m] - weight[n] + 2) % 2)
                {
                    cout << "In different gangs.\n";
                }
                else
                {
                    cout << "In the same gang.\n";
                }
            }
        }
        else
        {
            cout << "wrong command.\n";
        }
    }
};
