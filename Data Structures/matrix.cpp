struct Matrix {
    array<array<int, 2>, 2> mat = {0, 0, 0, 0};
    Matrix() {};
    Matrix(array<array<int, 2>, 2> mat) : mat(mat){};
    
    void print() {
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                cout << mat[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    Matrix operator* (const Matrix& other) {
        Matrix product;
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                for(int k = 0; k < 2; ++k) {
                    product.mat[i][k] = (product.mat[i][k] + 1ll*mat[i][j]*other.mat[j][k])%MOD;
                }
            }
        }
        return product;
    }
};
