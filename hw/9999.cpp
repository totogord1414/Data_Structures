// hope that one day i will understand this QAQ
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 高效并查集，用于 O(1) 合并倒塌墙壁两边的安全区块
struct DSU {
  vector<int> parent, left_bound, right_bound;
  DSU(int sz) {
    parent.resize(sz);
    left_bound.resize(sz);
    right_bound.resize(sz);
    for (int i = 0; i < sz; i++) {
      parent[i] = i;
      left_bound[i] = i;  // 记录这个连通块的最左界
      right_bound[i] = i; // 记录这个连通块的最右界
    }
  }
  int find(int i) {
    if (parent[i] == i)
      return i;
    return parent[i] = find(parent[i]);
  }
  void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
      parent[root_i] = root_j;
      // 合并时，新领土的边界是两者的最值扩展
      left_bound[root_j] = min(left_bound[root_j], left_bound[root_i]);
      right_bound[root_j] = max(right_bound[root_j], right_bound[root_i]);
    }
  }
};

int solve(vector<int> &a) {
  int n = a.size();
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;

  // 1. 离散化 (坐标压缩) 方便后续当数组索引
  vector<int> temp = a;
  sort(temp.begin(), temp.end());
  temp.erase(unique(temp.begin(), temp.end()), temp.end());
  for (int i = 0; i < n; ++i) {
    a[i] = lower_bound(temp.begin(), temp.end(), a[i]) - temp.begin();
  }
  int V = temp.size();

  // 记录每个值在数组中的所有出现位置 (升序)
  vector<vector<int>> pos(V);
  for (int i = 0; i < n; ++i) {
    pos[a[i]].push_back(i);
  }

  // 2. 预计算 LVS (Longest Valid Subsegment) 二维表 O(N^2)
  vector<vector<int>> LVS(n, vector<int>(n, 0));

  // 2.1 填入原生的无重复极大合法段
  for (int i = 0; i < n; ++i) {
    vector<bool> seen(V, false);
    for (int j = i; j < n; ++j) {
      if (seen[a[j]])
        break; // 遇到自身重复则截断
      seen[a[j]] = true;
      LVS[i][j] = j - i + 1;
    }
  }

  // 2.2 二维 DP 高效扩散，让 LVS[i][j] 存续它内部包含的最大可能长度
  for (int length = 2; length <= n; ++length) {
    for (int i = 0; i <= n - length; ++i) {
      int j = i + length - 1;
      LVS[i][j] = max({LVS[i][j], LVS[i + 1][j], LVS[i][j - 1]});
    }
  }

  int global_max_sum =
      LVS[0][n - 1]; // 全局最优解（预存只有 S1 没有 S2 的退化情况）

  // 3. 主算法：枚举 S2 起点 l2  (外层 O(N))
  for (int l2 = 1; l2 < n; ++l2) {
    // 第一步：贪心寻找 S2 在不自爆的情况下的极限 R_max
    int R_max = l2;
    vector<bool> in_s2(V, false);
    in_s2[a[l2]] = true;
    while (R_max + 1 < n && !in_s2[a[R_max + 1]]) {
      R_max++;
      in_s2[a[R_max]] = true;
    }

    // 第二步：在 [0, l2-1] 建立防御墙 / 障碍点
    int prefix_len = l2;
    DSU dsu(prefix_len);
    vector<bool> is_obstacle(prefix_len, false);

    // 凡是身在 S2 里的元素，在左边统统变成障碍
    for (int r = l2; r <= R_max; ++r) {
      int val = a[r];
      for (int p : pos[val]) {
        if (p < prefix_len)
          is_obstacle[p] = true;
        else
          break; // 由于 pos 是升序的，可以直接断开
      }
    }

    int current_max_s1 = 0;

    // 初始化左侧安全的无污染区块，合并相连的空地
    for (int i = 0; i < prefix_len; ++i) {
      if (!is_obstacle[i] && i > 0 && !is_obstacle[i - 1]) {
        dsu.unite(i, i - 1);
      }
    }

    // 获取初始状态下的最佳 max_S1
    for (int i = 0; i < prefix_len; ++i) {
      if (!is_obstacle[i] && dsu.find(i) == i) {
        int L = dsu.left_bound[i];
        int R = dsu.right_bound[i];
        current_max_s1 = max(current_max_s1, LVS[L][R]);
      }
    }

    // 第三步：魔术核心 —— 逆向回退时间轴 (内层摊销 O(N))
    for (int r2 = R_max; r2 >= l2; --r2) {

      // 此时 S2 是完整的 [l2 ... r2]，记录这一状态下的全局极致
      int current_s2_len = r2 - l2 + 1;
      global_max_sum = max(global_max_sum, current_max_s1 + current_s2_len);

      // 抛弃右端点 A[r2]，开始解放受其压迫的左方分身！
      int val = a[r2];
      for (int p : pos[val]) {
        if (p < prefix_len) {
          is_obstacle[p] = false; // 🧱 高墙倒塌！

          // 将这片刚清空的废墟，和它左右相邻的净土火速合并 (O(1))
          if (p > 0 && !is_obstacle[p - 1])
            dsu.unite(p, p - 1);
          if (p + 1 < prefix_len && !is_obstacle[p + 1])
            dsu.unite(p, p + 1);

          // 利用全新的广阔领土边界，进行 O(1) 查表直接打擂台更新！
          // （因为全是区间变大，所以 max_s1 是单调递增的，完美自洽）
          int root = dsu.find(p);
          int L = dsu.left_bound[root];
          int R = dsu.right_bound[root];
          current_max_s1 = max(current_max_s1, LVS[L][R]);
        } else {
          break;
        }
      }
    }
  }

  return global_max_sum;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (cin >> n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    cout << solve(a) << "\n";
  }
  return 0;
}
