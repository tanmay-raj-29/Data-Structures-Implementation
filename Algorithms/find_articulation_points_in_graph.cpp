int in[N], low[N];
int timer=0;

void isArticulation(int u) {
    
}

void dfs(int u,int par) {
    vis[u]=1;
    in[u] = low[u] = timer++;
    int children=0;
    for(int v: g[u]) {
        if(v == par) {
            continue;
        }
        if(vis[v]) {
            low[u]=min(low[u],in[v]);
        }
        else {
            dfs(v,u);
            low[u] = min(low[u], low[v]);
            if(par!=-1 && low[v]>=in[u]) {
                isArticulation(u);
            }
            children++;
        }
    }
    if(par==-1 && children>1) {
        isArticulation(u);
    }
}

void findArticulationPoint(int n) {
    timer = 0;
    memset(in, -1, sizeof(in));   
    memset(low, -1, sizeof(low)); 
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            dfs(i, -1);
        }
    }
}
