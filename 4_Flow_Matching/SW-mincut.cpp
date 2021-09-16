// global min cut
struct SW { // O(V^3) 0-based
  static const int MXN = 514;
  int n, vst[MXN], del[MXN];
  int edge[MXN][MXN], wei[MXN];
  void init(int _n) {
    n = _n, MEM(edge, 0), MEM(del, 0);
  }
  void addEdge(int u, int v, int w) {
    edge[u][v] += w, edge[v][u] += w;
  }
  void search(int &s, int &t) {
    MEM(vst, 0), MEM(wei, 0), s = t = -1;
    while (1) {
      int mx = -1, cur = 0;
      for (int i = 0; i < n; ++i)
        if (!del[i] && !vst[i] && mx < wei[i])
          cur = i, mx = wei[i];
      if (mx == -1) break;
      vst[cur] = 1, s = t, t = cur;
      for (int i = 0; i < n; ++i)
        if (!vst[i] && !del[i]) wei[i] += edge[cur][i];
    }
  }
  int solve() {
    int res = INF;
    for (int i = 0, x, y; i < n - 1; ++i) {
      search(x, y), res = min(res, wei[y]), del[y] = 1;
      for (int j = 0; j < n; ++j)
        edge[x][j] = (edge[j][x] += edge[y][j]);
    }
    return res;
  }
};
