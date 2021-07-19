vector<Edge> result;
int cost;
DSU dsu;

void kruskalMST(int n) {
    cost=0;
    dsu.init(n);
    
    sort(edges, edges+n);
    
    for (Edge e : edges) {
        if (dsu.getPar(e.u) != dsu.getPar(e.v)) {
            cost += e.weight;
            result.push_back(e);
            dsu.unite(e.u, e.v);
        }
    }
}