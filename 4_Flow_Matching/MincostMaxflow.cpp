struct MinCostMaxFlow {
    int maxn = 6025, INF = 1e9;
    int n, s, t;
    int rest[maxn][maxn];
    int w[maxn][maxn];
    int indeg[maxn];
    int dis[maxn];
    int prv[maxn];
    bool vis[maxn];
    int potential[maxn];
    void init(int _n) {
        n = _n + 2;
        s = _n + 1;
        t = _n + 2;
    }
    void addEdge(int a, int b, int cap, int cost) {
        rest[a][b] = cap;
        w[a][b] = cost;
        w[b][a] = -cost;
        ++indeg[b];
    }
    int cost(int a, int b) {
        return w[a][b] + potential[a] - potential[b];
    }
    void adjust_potential() {
        for (int i = 1; i <= n; i++) potential[i] += dis[i];
    }
    void sp() {
        // use sp when there are negative edges
        for (int i = 1; i <= n; i++) dis[i] = INF;
        dis[s] = 0;
        queue<int> q;
        q.emplace(s);
        while (!q.empty()) {
            int i = q.front(); q.pop();
            for (int j = 1; j <= n; j++) if (rest[i][j]) {
                dis[j] = min(dis[j], dis[i] + w[i][j]);
                if (--indeg[j] == 0)
                    q.emplace(j);
            }
        }
        adjust_potential();
    }
    bool dijkstra(int s, int t) {
        for (int i = 1; i <= n; i++) dis[i] = INF, vis[i] = false;
        dis[s] = 0;
        prv[s] = -1;
        for (int i = 1; i <= n; i++) {
            int x = -1;
            for (int j = 1; j <= n; j++) if (!vis[j] && (x == -1 || dis[x] > dis[j])) x = j;
            vis[x] = true;
            for (int j = 1; j <= n; j++) if (rest[x][j]) {
                if (dis[j] > dis[x] + cost(x, j)) {
                    dis[j] = dis[x] + cost(x, j);
                    prv[j] = x;
                }
            }
        }
        return dis[t] != INF;
    }
    pii MCMF() {
        ll cost = 0, flow = 0;
        while (dijkstra(s, t)) {
            int f = INF;
            for (int x = t; x != s; x = prv[x]) {
                int y = prv[x];
                f = min(f, rest[y][x]);
            }
            for (int x = t; x != s; x = prv[x]) {
                int y = prv[x];
                rest[y][x] -= f;
                rest[x][y] += f;
            }
            cost += f * (dis[t] - potential[s] + potential[t]);
            flow += f;
            adjust_potential();
        }
        return {flow, cost};
    }
} flow;