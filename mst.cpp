//@ Author : Vedant Kumud
//Algo/DS : Kruskal MST (Minimum Spanning Tree) Algorithm
//Build Complexity : O(MlogM)

#include <vector>
#include <algorithm>
#include <iostream>

bool cmp(const std::pair<std::pair<int, int>, int> &x, const std::pair<std::pair<int, int>, int> &y) {
  return x.second < y.second;
}

struct mst {
  std::vector<std::pair<std::pair<int, int>, int> > edges;
  std::vector<std::pair<int, int>> mst_edges;
  long long mst_cost;
  std::vector<int> parent, sz;
  
  void add(int u, int v, int w) {
    edges.push_back({{u, v}, w});
  }

  void init(int _n) {
    parent.resize(_n);
    for(int i = 0; i < _n; i++) {
      parent[i] = i;
    }
    sz.assign(_n, 1);
  }
  
  int find_set(int x) {
    return parent[x] == x ? x : parent[x] = find_set(parent[x]);
  }

  void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if(sz[a] < sz[b])
      std::swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
  }

  void generate_mst() {
    sort(edges.begin(), edges.end(), cmp);
    mst_cost = 0LL;

    for(auto &it : edges) {
      int x = it.first.first, y = it.first.second, w = it.second;
      if(find_set(x) == find_set(y))
        continue;
      union_set(x, y);
      mst_cost += w;
      mst_edges.push_back({x, y});
    }
  }
} mst_tree;

int main(){
  using namespace std;

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m; cin >> n >> m;
  
  mst_tree.init(n);
  for(int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    --u, --v;
    mst_tree.add(u, v, w);
  }

  mst_tree.generate_mst();

  cout << mst_tree.mst_cost << "\n";
  cout << n - 1 << "\n";
  for(auto &it : mst_tree.mst_edges) {
    cout << it.first + 1 << " " << it.second + 1 << "\n";
  }
}

