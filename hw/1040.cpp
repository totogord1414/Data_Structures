#include <bits/stdc++.h>

using namespace std;

class UnionFind
{
    private:

    vector<int> parent;
    vector<int> setSize;
    vector<int> nodeCount;
    int size;
    public:

    UnionFind(int n)
    {
        parent.resize(n + 1);
        setSize.resize(n + 1);
        nodeCount.resize(n + 1);
        for(int i = 1; i <= n; i++)
        {
            parent[i] = i;
            setSize[i] = 1;
            nodeCount[i] = 0;
        }
        size = n;
    }
    int Size()
    {
        return size;
    }

    int FindsetSize(int k)
    {
        int parentk = Find(k);
        return setSize[parentk];
    }
    void addCount(int k)
    {
        nodeCount[k] += 1;
    }

    int showCount(int k)
    {
        return nodeCount[k];
    }


    int Find(int k)
    {
        if(parent[k] != k)
        {
            parent[k] = Find(parent[k]);
        }
        return parent[k];
    }

    void Union(int x, int y)
    {
        int m = Find(x);
        int n = Find(y);
        if(m == n)
        {
            return;
        }
        if(setSize[m] < setSize[n])
        {
            swap(m, n);
        }
        parent[n] = m;
        setSize[m] += setSize[n];
    }
};

int check(UnionFind &uf)
{
    for(int i = 1; i <= uf.Size(); i++)
    {
        if(uf.showCount(i) % 2)
        {
            return 0;
        }
    }

    int first_edge_node = -1;
    for(int i = 1; i <= uf.Size(); i++)
    {
        if(uf.showCount(i) > 0)
        {
            int parent = uf.Find(i);
            if(first_edge_node == -1)
            {
                first_edge_node = parent;
            }
            else if(parent != first_edge_node)
            {
                return 0;
            }
        }
    }


    return 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    cin >> n >> m;
    UnionFind uf(n);
    for(int i = 0; i < m; i++)
    {
        int node1, node2;
        cin >> node1 >> node2;
        uf.addCount(node1);
        uf.addCount(node2);
        uf.Union(node1, node2);
    }

    int result = check(uf);

    cout << result << endl;
    return 0;
}