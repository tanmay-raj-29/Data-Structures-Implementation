vector<int> g[N], rg[N], todo;
int grp = 0;
int comp[N], sz[N];
bool vis[N];
set<int> gr[N];

void dfs(int u) {
    vis[u] = 1;
    for(auto &it:g[u]) {
        if(!vis[it])
            dfs(it);
    }
    todo.push_back(u);
}

void dfs2(int u, int val) {
    comp[u] = val;
    sz[val]++;
    for(auto &it:rg[u]) {
        if(comp[it] == -1)
            dfs2(it, val);
    }
}

void sccAddEdge(int from, int to) {
    g[from].push_back(to);
    rg[to].push_back(from);
}

void scc(int n) {
    for(int i = 1; i <= n; i++)
        comp[i] = -1;

    for(int i = 1; i <= n; i++) {
        if(!vis[i])
            dfs(i);
    }

    reverse(todo.begin(), todo.end());
    for(auto &it:todo) {
        if(comp[it] == -1)
            dfs2(it, ++grp);
    }
    
    // SCC Tree
    /*
    for(int i = 1; i <= n; i++)
        for(auto &it:g[i])
            if(comp[i] != comp[it])
                gr[i].insert(it);
    */
}