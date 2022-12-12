struct LCA {
private:
    vector<vector<int>> g, parent;
    vector<int> depth;
    int n = 0, LOG;
    
    void dfs(int u,int par=-1) {
        for(int& v:g[u]) {
            if(par != v) {
                parent[v][0] = u;
                depth[v] = depth[u] + 1;
                dfs(v,u);
            }
        }
    }

    int highest_bit(int x) {
        int max_bit = 0;
        for (int bit = 0; bit < 30; bit++) {
            if ((1 & (x >> bit))) max_bit = bit;
        }
        return max_bit;
    }

    int walk(int x,int h) {
        if (depth[x] < h) return -1;
        for(int i = LOG - 1; i >= 0; i--) {
            if(h & (1 << i)) {
                x = parent[x][i];
            }
        }
        return x;
    }
    
public:
    LCA(vector<vector<int>>& graph) {
        g = graph;
        n = g.size();
        depth.resize(n);
        LOG = highest_bit(n) + 1;
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i].resize(LOG);
        }
        dfs(0);
        for(int i = 1; i < LOG; i++) {
            for(int j = 0; j < n; j++) {
                parent[j][i] = parent[parent[j][i-1]][i-1];
            }
        }
    }

    int get_LCA(int a,int b) {
        if(depth[a] > depth[b]) swap(a, b); // depth[a] < depth[b]
        if(depth[a] != depth[b]) b = walk(b, depth[b] - depth[a]);
        if(a == b) {
            return a;
        }
        for(int i = LOG - 1; i >= 0; i--) {
            if(parent[a][i] != parent[b][i]) {
                a = parent[a][i];
                b = parent[b][i];
            }
        }
        return parent[a][0];
    }
    
    int distance(int a,int b) {
        return depth[a] + depth[b] - 2 * depth[get_LCA(a,b)];
    }
};
