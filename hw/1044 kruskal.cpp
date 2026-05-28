#include <bits/stdc++.h>

using namespace std;

struct road{
    int u;
    int v;
    int cost;

};

struct UnionFind{
    vector<int> parent;
    vector<int> setSize;
    int size;
    
    UnionFind(int n){
        size = n;
        parent.resize(n + 1);
        setSize.resize(n + 1, 1);
        for(int i = 1; i <= n; i++){
            parent[i] = i;
        }
    }

    int Find(int startNode)
    {
        if(startNode != parent[startNode])
        {
            parent[startNode] = Find(parent[startNode]);
        }
        return parent[startNode];
    }

    void Union(int u, int v)
    {
        int uParent = Find(u);
        int vParent = Find(v);
        if(uParent != vParent){
            if(setSize[uParent] < setSize[vParent]){
                swap(uParent, vParent);
            }
            parent[vParent] = uParent;
            setSize[uParent] += setSize[vParent];
        }
    }

    bool inSameSet(int u , int v)
    {
        int parent1 = Find(u);
        int parent2 = Find(v);

        return parent1 == parent2;
    }
};

bool cmp(const road& a, const road& b)
{
    return a.cost < b.cost;
}

int solve(int N, vector<road>& roadSet, UnionFind& uf){
    int lowestCost = 0;
    int currRoad = 0;
    int roadPointer = 0;
    while(roadPointer < roadSet.size() && currRoad < N - 1)
    {
        int u = roadSet[roadPointer].u;
        int v = roadSet[roadPointer].v;
        if(!uf.inSameSet(u, v))
        {
            uf.Union(u, v);
            currRoad++;
            lowestCost += roadSet[roadPointer].cost;
        }
        roadPointer++;
    }

    if(currRoad < N - 1)
    {
        return -1;
    }
    else{
        return lowestCost;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);   

    int N, M;
    cin >> N >> M;
    UnionFind uf(N);
    vector<road> roadSet;
    for(int i = 0; i < M; i++)
    {
        int u, v, cost;
        cin >> u >> v >> cost;
        roadSet.push_back({u, v, cost});
    }
    sort(roadSet.begin(), roadSet.end(), cmp);

    int ans = solve(N, roadSet, uf);
    
    cout << ans << "\n";

    return 0;
}