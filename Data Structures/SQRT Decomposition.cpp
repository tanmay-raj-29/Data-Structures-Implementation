struct sqrt_dec {
    int n;
    int block_size;
    vector<int> a;
    vector<long long> block;
    
    sqrt_dec(vector<int>& v) {
        n = v.size();
        block_size = sqrt(n) + 1;
        a.resize(n);
        block.resize(sqrt(n)+1, 0);
        int b = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            a[i] = v[i];
            block[b] += a[i];
            cnt++;
            if (cnt == block_size) {
                b++;
                cnt = 0;
            }
        }
    }
    void upd(int i, int val) {
        block[i / block_size] += val - a[i];
        a[i] = val;
    }
    long long query(int l, int r) {
        long long ans = 0;
        int b_l = l / block_size, b_r = r / block_size;
        if(b_l == b_r) {
            for (int i = l; i <= r; i++) {
                ans += a[i];
            }
        }
        else {
            int j = (b_l+1) * block_size - 1;
            for (int i=l; i <= j; i++) {
                ans += a[i];
            }
            for (int i = b_l + 1; i < b_r; i++)
                ans += block[i];
            for (int i = b_r * block_size; i <= r; i++)
                ans += a[i];
        }
        return ans;
    }
};
