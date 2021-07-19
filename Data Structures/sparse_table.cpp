int logs[N]; // logs[i] means such maximum p that 2^p <= i
int st[20][N];

void computeLogs() {
    logs[1] = 0;
    for(int i = 2; i <= N; i++) {
        logs[i] = logs[i / 2] + 1;
    }
}

void buildSparseTable(vector<int>& a) {
    int n = a.size();
    for(int i = 0; i <= logs[n]; i++) {
        int curLen = 1 << i; // 2^i
        for(int j = 0; j + curLen <= n; j++) {
            if (curLen == 1) {
                st[i][j] = a[j];
            } 
            else {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (curLen / 2)]);
            }
        }
    }
}

int getANS(int l, int r) {
    if(l>r || l<0 || r>=n) {
        return mod;
    }
    int p = logs[r - l + 1];
    int pLen = 1 << p; // 2^p
    return max(st[p][l], st[p][r - pLen + 1]);
}