struct Matrix {
    int n = 0, m = 0;
    vector<vector<int>> mat;
    Matrix() {};
    Matrix(int _n, int _m) {n = _n; m = _m; mat.assign(n, vector<int>(m, 0)); }
    Matrix(vector<vector<int>> v) { n = v.size(); m = n ? v[0].size() : 0; mat = v; }
    void make_unit() {
        assert(n == m);
        for(int i = 0; i < n; i++)  {
            for(int j = 0; j < n; j++) {
                mat[i][j] = (i == j);
            }
        }
    }
    Matrix operator + (const Matrix &b) {
        assert(n == b.n && m == b.m);
        Matrix res = Matrix(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                res.mat[i][j] = (mat[i][j] + b.mat[i][j]) % MOD;
            }
        }
        return res;
    } 
    Matrix operator - (const Matrix &b) {
        assert(n == b.n && m == b.m);
        Matrix res = Matrix(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                res.mat[i][j] = (mat[i][j] - b.mat[i][j] + MOD) % MOD;
            }
        }
        return res;
    }
    Matrix operator * (const Matrix &b) {
        assert(m == b.n);
        Matrix res = Matrix(n, b.m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < b.m; j++) {
                for(int k = 0; k < m; k++) {
                    res.mat[i][j] = (res.mat[i][j] + 1LL * mat[i][k] * b.mat[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }
    Matrix pow(long long k) {
        assert(n == m);
        Matrix res(n, n), t = mat; res.make_unit();
        while(k > 0) {
            if(k % 2) res = res * t;
            t = t * t;
            k /= 2;
        }
        return res;
    }
    Matrix& operator += (const Matrix& b) { return *this = (*this) + b; }
    Matrix& operator -= (const Matrix& b) { return *this = (*this) - b; }
    Matrix& operator *= (const Matrix& b) { return *this = (*this) * b; }
    bool operator == (const Matrix& b) { return mat == b.mat; }
    bool operator != (const Matrix& b) { return mat != b.mat; }
};