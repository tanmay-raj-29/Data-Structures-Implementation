struct SCC {
    vector<vector<int>> g, rg, components;
    vector<int> order, index;
    int n;

    void build_reverse_graph() {
        rg.clear();
        rg.resize(n);
        for (int u = 0; u < n; u++) {
            for (int v : g[u]) {
                rg[v].push_back(u);
            }
        }
    }
    void dfs1(int u, vector<bool>& vis) {
        vis[u] = true;
        for (int v : g[u]) {
            if (!vis[v]) dfs1(v, vis);
        }
        order.push_back(u);
    }
    void dfs2(int u, vector<bool>& vis, vector<int>& cmp) {
        cmp.push_back(u);
        vis[u] = true;
        for (int v : rg[u]) {
            if (!vis[v]) dfs2(v, vis, cmp);
        }
    }
public:
    SCC(vector<vector<int>>& g) : g(g) {
        n = (int)g.size();
        index.resize(n);
    }
    void init() {
        build_reverse_graph();
        
        vector<bool> vis(n, false);
        for (int u = 0; u < n; u++) {
            if (!vis[u]) dfs1(u, vis);
        }
        vis = vector<bool>(n, false);
        reverse(order.begin(), order.end());
        for (int u : order) {
            if (!vis[u]) {
                vector<int> cmp;
                dfs2(u, vis, cmp);
                for (int el : cmp) {
                    index[el] = (int)components.size();
                }
                components.push_back(cmp);
            }
        }
    }
    vector<int> get_component(int u) { return components[index[u]]; }
    bool is_first(int u) { return components[index[u]].front() == u; }
};