// @ Author : Vedant Kumud
// Algo/DS : Centroid Tree Decomposition
// Build Complexity: O(NlogN)
// Query Complexity: O(logN*f)
// Update Complexity: O(logN*f)

#include <set>
#include <vector>
#include <iostream>

struct centroid {
  std::vector<std::set<int>> adj;
  std::vector<int> sz;
  std::vector<int> par;

  void get_size(int c, int p) {
    sz[c] = 1;
    for(int next : adj[c]) {
      if(next == p)
        continue;
      get_size(next, c);
      sz[c] += sz[next];
    }
  }

  int find_centroid(int c, int p, int n) {
    for(int next : adj[c]) {
      if(next == p) continue;
      if(sz[next] > n/2)
        return find_centroid(next, c, n);
    }
    return c;
  }

  void init(int c, int p) {
    get_size(c, p);
    int x = find_centroid(c, p, sz[c]);
    if(p == -1) par[x] = x;
    else par[x] = p;
    for(auto next : adj[x]) {
      adj[next].erase(x);
      init(next, x);
    }
    adj[x].clear();
  }

  void init(int _n) {
    adj.resize(_n);
    sz.resize(_n);
    par.resize(_n);
  }

  void add(int a, int b) {
    adj[a].insert(b);
    adj[b].insert(a);
  }

} centroid_tree;

int main() {
  using namespace std;

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  for(int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    centroid_tree.add(u, v);
  }
}
