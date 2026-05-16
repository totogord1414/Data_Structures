#include <bits/stdc++.h>

using namespace std;

class UnionFind
{
private:
    vector<int> parent;
    vector<int> size;
    int max_size;
public:
 UnionFind(int n)
 {
    parent.resize(2* n + 1);
    size.resize(2 * n + 1, 1);
    max_size = n;
    for(int i = 0; i <= 2 * n; i++)
    {
        parent[i] = i;
    }
 }

 int Find(int n)
 {
    if(parent[n] != n)
    {
        parent[n] = Find(parent[n]);
    }
    return parent[n];
 }

 void Union(int m, int n)
 {
    int x = Find(m);
    int y = Find(n);
    if(x != y)
    {
        if(size[x] < size[y])
        {
            swap(x, y);
        }
        size[x] += size[y];
        parent[y] = x;
    }
 }

 void read_command(char command, int x, int y)
 {
    if(command == 'A')
    {
        Union(x, max_size + y);
        Union(x + max_size, y);
    }
    else if (command == 'Q')
    {
        if(Find(x) == Find(y))
        {
            cout << "In the same gang.\n";
        }
        else if(Find(x) == Find(max_size + y))
        {
            cout << "In different gangs.\n";
        }
        else
        {
            cout << "Not sure yet.\n";
        }
    }
    else
    {
        cout << "command error" << endl;
    }
 }
};


int main()
{
    ios_base:: sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        int n, m;
        cin >> n >> m;
        UnionFind uf(n);
        for(int j = 0; j < m; j++)
        {
            char c;
            int x, y;
            cin >> c >> x >> y;
            uf.read_command(c, x, y);
        }
    }
    return 0;
}