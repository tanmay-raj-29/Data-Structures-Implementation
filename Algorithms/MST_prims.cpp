int dist[N], parent[N];
vector<array<int, 2>> tree[N];
bool vis[N];

long long primsMST(int source, int n) { //Finds the cost and makes the MST
    for (int i = 0; i < n; i++) {
        dist[i] = 1e9;
        vis[i] = false;
    }
    set<array<int, 2>> s;
    s.insert({0, source});
    long long cost = 0;
    dist[source] = 0;
    while(!s.empty()) {
        array<int, 2> node = *(s.begin());
        s.erase(node);
        cost += node[0];
        int u = node[1];
        int p = parent[u];
        int weight = node[0];
        tree[u].push_back({p, weight});
        tree[p].push_back({u, weight});
        vis[u] = 1;
        for(auto it:g[u]) {
            int v = it[0], w = it[1];
            if(!vis[v] && dist[v] > w) {
                s.erase({dist[v], v});
                dist[v] = w;
                s.insert({dist[v], v});
                parent[v] = u;
            }
        }
    }
    return cost;
}