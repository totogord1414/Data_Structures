#include <bits/stdc++.h>

using namespace std;

class FindUnion
{
private:
    vector<int> parent;
    vector<int> size;
    int max_size;
public:
 /*the init function*/
 FindUnion(int n)
 {
    size.resize(n, 1);
    parent.resize(n);
    max_size = 1;
    for(int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
 }

/*the find function*/
 int Find(int n)
 {
    if(parent[n] != n)
    {
        parent[n] = Find(parent[n]);
    }
    return parent[n];
 }

 void Union(int x, int y)
 {
    int x_root = Find(x);
    int y_root = Find(y);
    if(x_root != y_root)
    {
        if(size[x_root] > size[y_root])
        {
            swap(x_root, y_root);
        }
        parent[x_root] = y_root;
        size[y_root] += size[x_root];
        max_size = max(max_size, size[y_root]);
    }
 }

 int MaxSize()
 {
    return max_size;
 }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    FindUnion uf(n);
    for(int i = 0; i < m; i++)
    {
        int t;
        cin >> t;
        if(t == 0) continue;
        int first;
        cin >> first;
        for(int j = 1; j < t; j++)
        {
            int temp;
            cin >> temp;
            uf.Union(first - 1, temp - 1);
        }
    }
    cout << uf.MaxSize() << endl;
    return 0; 
}