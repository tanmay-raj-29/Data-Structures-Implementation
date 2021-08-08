int in[N];   // entry time 
int low[N];  // lowest entry time for the component
int timer=0;

void isBridge(int u,int v) {
    
}

void dfs(int u,int par) {
    vis[u] = 1;
    in[u] = low[u] = timer++;
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
            if(low[v] > in[u]) {
                isBridge(u,v);
            }
        }
    }
}

void findBridge(int n)
{
    timer = 0;
    memset(in,-1,sizeof(in));   
    memset(low,-1,sizeof(low)); 
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) dfs(i, -1);
    }
}