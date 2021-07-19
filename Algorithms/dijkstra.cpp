int dijkstra(int source, int target, vector<int>& dist, vector<vector<array<int, 2>>>& g) {
    int n = dist.size();
    for(int i = 0; i <= n; ++i) {
        dist[i] = 1e9;
    }
    set<array<int, 2>> s;
    s.insert({0, source});
    dist[source] = 0;
    while(!s.empty()) {
        int u = (*s.begin())[1];
        s.erase(s.begin());
        for(auto& it:g[u]) {
            int v = it[0], w = it[1];
            if(dist[v] > dist[u] + w) {
                s.erase({dist[v], v});
                dist[v] = dist[u] + w;
                s.insert({dist[v], v});
            }
        }
    }
    return dist[target];
}