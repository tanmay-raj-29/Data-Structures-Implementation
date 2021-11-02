const int LOG=20;
int depth[N];
int parent[N][LOG];

void dfs(int u,int par=-1) {
    for(int& v:g[u]) {
        if(par != v) {
            parent[v][0]=u;
            depth[v] = depth[u]+1;
            dfs(v,u);
        }
    }
}

void precompute() {
    dfs(0);
    for(int i=1;i<LOG;i++) {
        for(int j=0;j<n;j++) {
            parent[j][i] = parent[parent[j][i-1]][i-1];
        }
    } 
}

int walk(int x,int h) {
    for(int i=LOG-1;i>=0;i--) {
        if(h&(1<<i)) {
            x=parent[x][i];
        }
    }
    return x;
}

int LCA(int a,int b) {
    if(depth[a] > depth[b]) swap(a,b); // depth[a] < depth[b]
    if(depth[a] != depth[b]) b=walk(b,depth[b]-depth[a]);
    if(a == b) {
        return a;
    }
    for(int i=LOG-1;i>=0;i--) {
        if(parent[a][i] != parent[b][i]) {
            a=parent[a][i];
            b=parent[b][i];
        }
    }
    return parent[a][0];
}

int distance(int a,int b) {
    return depth[a] + depth[b] - 2*depth[LCA(a,b)];
}