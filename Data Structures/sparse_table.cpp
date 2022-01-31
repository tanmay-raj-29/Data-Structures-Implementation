template<typename T>
struct SPARSE_TABLE {
    T apply(T a, T b) {
        // change according to operation
        return gcd(a, b);
    }
    
    int highest_bit(int x) {
        int max_bit = 0;
        for (int bit = 0; bit < 30; bit++) {
            if ((1 & (x >> bit))) max_bit = bit;
        }
        return max_bit;
    }
 
    int n = 0;
    vector<vector<T>> st;
 
    SPARSE_TABLE(const vector<T> &values = {}) {
        if (!values.empty()) build(values);
    }
 
    void build(const vector<T> &values) {
        n = int(values.size());
        int levels = highest_bit(n) + 1;
        st.resize(levels);
 
        for (int k = 0; k < levels; k++) {
            st[k].resize(n - (1 << k) + 1);
        }

        if (n > 0) st[0] = values;
 
        for (int k = 1; k < levels; k++) {
            int cur_len = (1 << k); // 2 ^ k
            for (int i = 0; i + cur_len <= n; i++) {
                st[k][i] = apply(st[k - 1][i], st[k - 1][i + (cur_len / 2)]);
            }
        }
    }

    T query(int L, int R) {
        assert(0 <= L && L <= R && R < n);
        int level = highest_bit(R - L + 1);
        int len = (1 << level);
        return apply(st[level][L], st[level][R - len + 1]);
    }
};