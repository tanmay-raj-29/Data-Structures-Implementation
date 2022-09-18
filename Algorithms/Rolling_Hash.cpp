struct Hash {
    const int P = 31;
    const int M = 1e9 + 7;
    vector<int> hash, R_hash, inverse, R_inverse;
    string S, R_S;
    int n;

    void init(const string& x, vector<int>& dp, vector<int>& inv) {
        int base = 1;
        inv[0] = 1;
        dp[0] = (x[0] - 'a' + 1);

        for (int i = 1; i < n; i++) {
            base = 1LL * base * P % M;
            inv[i] = modpow(base, M - 2);

            dp[i] = (dp[i - 1] + 1LL * (x[i] - 'a' + 1) * base) % M;
        }
    }

    Hash(const string& s) {
        n = (int)s.size();
        S = s;
        R_S = s;
        reverse(R_S.begin(), R_S.end());

        hash.resize(n);
        R_hash.resize(n);
        inverse.resize(n);
        R_inverse.resize(n);

        init(S, hash, inverse);
        init(R_S, R_hash, R_inverse);
        reverse(R_hash.begin(), R_hash.end());
        reverse(R_inverse.begin(), R_inverse.end());
    }

    int modpow(int base, long long exp) {
        int res = 1;
        while (exp > 0) {
            if (exp % 2 == 1) res = 1LL * res * base % M;
            
            exp /= 2;
            base = 1LL * base * base % M;
        }
        return res;
    }

    int get_hash(int L, int R) {
        if (R < L) return -1;
        int h = hash[R];
        if (L > 0) h -= hash[L - 1];
        h += M;
        return 1LL * h * inverse[L] % M;
    }

    int get_reverse_hash(int L, int R) {
        if (R < L) return -1;
        int h = R_hash[L];
        if (R != n - 1) h -= R_hash[R + 1];
        h += M;
        return 1LL * h * R_inverse[R] % M;
    }

    bool check_pallindrome(int L, int R) {
        if (R <= L) return true;
        int mid = L + (R - L) / 2;
        if ((R - L + 1) % 2 == 0) return get_hash(L, mid) == get_reverse_hash(mid + 1, R);
        else return get_hash(L, mid - 1) == get_reverse_hash(mid + 1, R);
    }
};
