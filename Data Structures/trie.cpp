struct TRIE {
    vector<vector<array<int, 2>>> nxt; // {address, cnt}
    int total;

    TRIE() {
        nxt.push_back(vector<array<int, 2>>(2, {0, 0}));
        total = 0;
    }

    void add(int x) {
        int node = 0;
        for(int bit = 19; bit >= 0; --bit) {
            int b = (1 & (x >> bit));
            if(nxt[node][b][0] == 0) {
                nxt[node][b][0] = ++total;
                nxt.push_back(vector<array<int, 2>>(2, {0, 0}));    
            }
            nxt[node][b][1]++;
            node = nxt[node][b][0];
        }
    }

    void del(int x) {
        int node = 0;
        for(int bit = 19; bit >= 0; --bit) {
            int b = (1 & (x >> bit));
            nxt[node][b][1]--;
            node = nxt[node][b][0];
        }
    }

    int search(int x) {
        int node = 0, ans = 0;
        for(int bit = 19; bit >= 0; --bit) {
            int b = (1 & (x >> bit));
            int a = !b;
            if(nxt[node][a][1] == 0) {
                a ^= 1;
            }
            node = nxt[node][a][0];
            ans += (a ^ b)*(1 << bit);
        }
        return ans;
    }
};