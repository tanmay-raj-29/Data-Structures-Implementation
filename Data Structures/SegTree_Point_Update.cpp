struct Data {
    int el = 0;
    Data() {}
    Data(int el) : el(el) {}

    void merge(const Data& left, const Data& right) {
        el = left.el + right.el;
    }
};

struct SegTree {
    int LEN;
    vector<Data> st;
    Data id_el;

    void build(int node, const vector<int>& arr, int L, int R) {
        if (L == R) {
            st[node] = Data(arr[L]);
            return;
        }
        int mid = L + (R - L) / 2;
        build(2 * node, arr, L, mid);
        build(2 * node + 1, arr, mid + 1, R);
        st[node].merge(st[2 * node], st[2 * node + 1]);
    }

    Data query(int node, int L, int R, int qL, int qR) {
        if (L > qR || R < qL) return id_el;
        if (qL <= L && R <= qR) return st[node];
        int mid = L + (R - L) / 2;
        Data left = query(2 * node, L, mid, qL, qR);
        Data right = query(2 * node + 1, mid + 1, R, qL, qR);
        Data ans;
        ans.merge(left,right);
        return ans;
    }

    void update(int node, int L, int R, int point, int val) {
        if (L > point || R < point) return;
        if (L == R) {
            st[node] = Data(val);
            return;
        }
        int mid = L + (R - L) / 2;
        update(2 * node, L, mid, point, val);
        update(2 * node + 1, mid + 1, R, point, val);
        st[node].merge(st[2 * node], st[2 * node + 1]);
    }

public:
    SegTree(int n) {
        LEN = n;
        st.resize(4 * LEN);
        id_el = Data();
    }
    void build(const vector<int>& arr) {
        build(1, arr, 0, LEN - 1);
    }
    Data query(int qL, int qR) {
        return query(1, 0, LEN - 1, qL, qR);
    }
    void update(int point, long long val) {
        update(1, 0, LEN - 1, point, val);
    }
};