struct DSU {
    int connected;
    vector<int> par, sz;
    DSU() {};
    DSU (int n)  {
        par = sz = vector<int> (n + 1, 0);
        for(int i = 0; i <= n; i++)
            par[i] = i, sz[i] = 1;
        connected = n;
    }

    int getPar(int u) {
        if (u == par[u]) return u;
        return par[u] = getPar(par[u]);
    }

    int getSize(int u) {
        return sz[getPar(u)];
    }

    bool merge(int u, int v) {
        int par1 = getPar(u), par2 = getPar(v);
        if(par1 == par2) {
            return false;
        }
        sz[par2] += sz[par1];
        sz[par1] = 0;
        par[par1] = par[par2];
        connected--;
        return true;
    }
};