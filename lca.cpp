// @ Author : Vedant Kumud
// Algo/DS : LCA (Least Common Ancestor)
// Build Complexity: O(NlogN)
// Query Complexity: O(logN)

#include <vector>
#include <set>
#include <iostream>

struct lca {
  const int LOG = 20;
  std::vector<std::vector<int>> adj;
  std::vector<std::vector<int>> par;
  std::vector<int> depth;

  void init(int _n) {
    adj.resize(_n);
    par.resize(_n, std::vector<int>(LOG));
    depth.resize(_n, 0);
  }

  void add(int a, int b) {
		adj[a].push_back(b);
    adj[b].push_back(a);
  }

  void dfs(int c, int p) {
    for(int next : adj[c]) {
      if(next == p) continue;
      par[next][0] = c;
      depth[next] = depth[c] + 1;
      dfs(next, c);
    }
  }

  void init_tab(int _n) {
    for(int j=1;j<LOG;j++) {
      for(int i=0;i<_n;i++) {
        par[i][j] = par[ par[i][j-1] ][j-1];
      }
    }
  }

  int anc(int u, int v) {
    if(depth[u] < depth[v])
      std::swap(u, v);

    for(int i = LOG - 1; i >= 0; i--) {
      if(depth[u] - (1 << i) >= depth[v])
        u = par[u][i];
    }

    if(u == v)
      return u;

    for(int i = LOG - 1; i >= 0; i--) {
      if(par[u][i] == par[v][i]) continue;
      u = par[u][i], v = par[v][i];
    }

    return par[v][0];
  }

} lca_tree;

int main() {
  using namespace std;

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q; cin >> n >> q;
  
  lca_tree.init(n);
  for(int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    lca_tree.add(u, v);
  }
  lca_tree.dfs(0, -1);
  lca_tree.init_tab(n);
  for(int i = 0; i < q; i++) {
    int x, y; cin >> x >> y;
    --x, --y;
    cout << lca_tree.anc(x, y) << "\n";
  }
}
