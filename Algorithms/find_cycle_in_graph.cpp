int parent[N], cycle_end, cycle_start;

bool detectCycle(int u, int par) {
    vis[u]=1;
    for(int &v:g[u]) {
        if(v == par) continue;  // for undirected graph skip parent
        if(vis[v] == 0) {
            parent[v] = u;
            if(detectCycle(v, u)) {
                return true;
            } 
        }
        else if(vis[v] == 1) {
            cycle_end = u;
            cycle_start = v;
            return true;
        }
    }
    vis[u] = 2;
    return false;
}

void findCycle(int n) {
    memset(parent, -1, sizeof(parent));
    cycle_start = -1;
    for(int i = 1; i <= n; ++i) {
        if(!vis[i] && detectCycle(i,-1)) {
            break;
        }
    }
    if(cycle_start == -1) {
        // no cycle
    }    
    else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());
        cout<< cycle.size() << "\n";
        for(auto &it:cycle) {
            cout<<it<<" ";
        }
    }
}