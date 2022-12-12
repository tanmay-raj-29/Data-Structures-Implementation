struct LCA {
private:
    vector<vector<int>> g, sparse, parent;
    vector<int> depth, euler, pos;
    int n = 0, LOG = -1, sz;
    
    void dfs(int u, int par = -1) {
        parent[u][0] = par;
        pos[u] = (int)euler.size();
        euler.push_back(u);
        for(int& v : g[u]) {
            if(par != v) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
                euler.push_back(u);
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

    inline int apply(int u, int v) {
        return depth[u] <= depth[v] ? u : v;
    }

    void build() {
        sz = (int)euler.size();
        int levels = highest_bit(sz) + 1;
        sparse.resize(levels);
 
        for (int k = 0; k < levels; k++) {
            sparse[k].resize(sz - (1 << k) + 1);
        }

        if (sz > 0) sparse[0] = euler;
 
        for (int k = 1; k < levels; k++) {
            int cur_len = (1 << k); // 2 ^ k
            for (int i = 0; i + cur_len <= sz; i++) {
                sparse[k][i] = apply(sparse[k - 1][i], sparse[k - 1][i + (cur_len / 2)]);
            }
        }
    }

    int query(int L, int R) {
        assert(0 <= L && L <= R && R < sz);
        int level = highest_bit(R - L + 1);
        int len = (1 << level);
        return apply(sparse[level][L], sparse[level][R - len + 1]);
    }
public:
    LCA(vector<vector<int>>& graph) {
        g = graph;
        n = (int)g.size();
        depth.resize(n);
        parent.resize(n);
        pos.resize(n);
        LOG = highest_bit(n) + 1;
        for (int i = 0; i < n; i++) {
            parent[i].resize(LOG);
        }
        dfs(0);
        for(int i = 1; i < LOG; i++) {
            for(int j = 0; j < n; j++) {
                if (parent[j][i - 1] == -1) parent[j][i] = -1;
                else parent[j][i] = parent[parent[j][i-1]][i-1];
            }
        }
        build();
    }

    int walk(int x,int h) {
        if (depth[x] < h) return -1;
        for(int i = LOG - 1; i >= 0; i--) {
            if(h & (1 << i)) {
                x = parent[x][i];
                if (x == -1) return -1;
            }
        }
        return x;
    }

    int get_LCA(int a, int b) {
        if (pos[a] > pos[b]) swap(a, b);
        return query(pos[a], pos[b]);
    }
    
    int distance(int a, int b) {
        deb(depth[a], depth[b]);
        deb(get_LCA(a, b));
        deb(euler);
        return depth[a] + depth[b] - 2 * depth[get_LCA(a, b)];
    }
};