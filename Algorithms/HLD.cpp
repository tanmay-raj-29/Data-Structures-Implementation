// add value to all nodes in subtree
// find max value of node in path between u and v
// https://www.hackerrank.com/challenges/subtrees-and-paths/problem

struct Data {
    int el = -MOD;

    Data() {};
    Data(int val) {
        el = val;
    }
    
    void merge(const Data &left, const Data &right) {
        el = max(left.el, right.el);
    }
};

struct update {
    int v = 0; 
    
    update(){};
    update(int val) : v(val) {};
    
    void combine(update &other, const int &tl, const int &tr) {
        v += other.v;
    }
    
    void apply(Data &x, const int &tl, const int &tr) {
        x.el += v;
        v=0;
    }
};


struct segTree {
    int len;
    vector<Data> st;
    vector<update> u;
    vector<bool> lazy;
    Data id_el;
    update id_tr;

    segTree() {};
    segTree(int l) {
        len = l;
        st.resize(4 * len);
        u.resize(4 * len);
        lazy.resize(4 * len);
        id_el = Data();
        id_tr = update();
    }
    
    void propagate(int node, int tl, int tr) {
        if(!lazy[node]) {
            return;
        }
        int tm = tl + (tr - tl) / 2;
        apply(2 * node, tl, tm, u[node]);
        apply(2 * node + 1, tm + 1, tr, u[node]);
        u[node] = id_tr;
        lazy[node] = 0;
    }
    
    void apply(int node, int tl, int tr, update upd) {
        if(tl != tr) {
            lazy[node] = 1;
            u[node].combine(upd, tl, tr);
        }
        upd.apply(st[node], tl, tr);
    }
    
    void build(const vector<int> &arr, int node, int tl, int tr) {
        if(tl == tr) {
            st[node] = Data(arr[tl]);
            return;
        }
        int tm = tl + (tr - tl) / 2;
        build(arr, 2 * node, tl, tm);
        build(arr, 2 * node + 1, tm+1, tr);
        st[node].merge(st[2 * node], st[2 * node + 1]);
    }
    
    Data query(int node, int tl, int tr, int l, int r) {
        if(l > tr || r < tl) {
            return id_el;
        }
        if(tl >= l && tr <= r) {
            return st[node];
        }
        propagate(node, tl, tr);
        int tm = tl + (tr - tl) / 2;
        Data a = query(2 * node, tl, tm, l, r), b = query(2 * node + 1, tm+1, tr, l, r), ans;
        ans.merge(a, b);
        return ans;
    }
    
    void rupd(int node, int tl, int tr, int l, int r, update &upd) {
        if(l > tr || r < tl) {
            return;
        }
        if(l <= tl && tr <= r) {
            apply(node, tl, tr, upd);
            return;
        }
        propagate(node, tl, tr);
        int tm = tl + (tr - tl) / 2;
        rupd(2 * node, tl, tm, l, r, upd);
        rupd(2 * node + 1, tm+1, tr, l, r, upd);
        st[node].merge(st[2 * node], st[2 * node + 1]);
    }
    
    void build() {
        vector<int> arr(len);
        build(arr, 1, 0, len-1);
    }
    Data query(int l,  int r) {
        return query(1, 0, len-1, l, r);
    }
    void rupd(int l, int r, update &upd) {
        rupd(1, 0, len-1, l, r, upd);
    }
};

struct HLD {
    const int root = 0;
    vector<vector<int>> g;
    segTree sgt;
    int n;

    vector<int> parent, depth, heavy, head, pos, in, out;
    int cur_pos;

    int dfs(int v, vector<vector<int>> const& adj) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                int c_size = dfs(c, adj);
                size += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }
        }
        return size;
    }

    void decompose(int v, int h, vector<vector<int>> const& adj) {
        head[v] = h;
        in[v] = cur_pos;
        pos[v] = cur_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h, adj);
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, adj);
        }
        out[v] = cur_pos;
    }

    void init(vector<vector<int>> const& adj) {
        n = adj.size();
        parent = vector<int>(n);
        in = vector<int>(n);
        out = vector<int>(n);
        depth = vector<int>(n);
        heavy = vector<int>(n, -1);
        head = vector<int>(n);
        pos = vector<int>(n);
        cur_pos = 0;

        dfs(0, adj);
        decompose(0, 0, adj);
    }

    HLD(vector<vector<int>>& adj) {
        g = adj;
        
        init(adj);
        sgt = segTree(n);
        sgt.build();
    }

    int query(int a, int b) {
        int res = -MOD;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            int cur_heavy_path_max = sgt.query(pos[head[b]], pos[b]).el;
            res = max(res, cur_heavy_path_max);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int last_heavy_path_max = sgt.query(pos[a], pos[b]).el;
        res = max(res, last_heavy_path_max);
        return res;
    }


    void update_sub(int a, int val) {
        update upd(val);
        sgt.rupd(in[a], out[a] - 1, upd);
    }
};