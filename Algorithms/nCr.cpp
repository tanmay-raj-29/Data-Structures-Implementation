namespace modop {
    const int mod = 1e9 + 7;
    inline int modadd(int a, int b) {return (a + b) % mod;}
    inline int modsub(int a, int b) {return (a % mod - b % mod + mod) % mod;}
    inline int modmul(int a, int b) {return (1LL * (a % mod) * (b % mod)) % mod;}
    int modpow(int base, long long exp) {
        int res = 1;
        while (exp > 0) {
            if (exp % 2 == 1) {
                res = modmul(res, base);
            }
            exp /= 2;
            base = modmul(base, base);
        }
        return res;
    }
    int modinv(int base) {return modpow(base, mod - 2);}
    int moddiv(int a, int b) {return modmul(a, modinv(b));}
    
    const int FACTORIAL_SIZE = 3e5+5;
    int fact[FACTORIAL_SIZE+1], invfact[FACTORIAL_SIZE+1];
    bool generated_factorials__ = false;

    void generate_factorials() {
        fact[0] = fact[1] = invfact[0] = invfact[1] = 1;
        
        for (int i = 2; i <= FACTORIAL_SIZE; i++) {
            fact[i] = modmul(i, fact[i-1]);
        }
        invfact[FACTORIAL_SIZE] = modinv(fact[FACTORIAL_SIZE]);
        for (int i = FACTORIAL_SIZE - 1; i >= 2; i--) {
            invfact[i] = modmul(i+1, invfact[i+1]);
        }
    }
    int nCr(int n, int r) {
        if(generated_factorials__ == false) {
            generate_factorials();
        }
        return (r < 0 || n < r) ? 0 : modmul(modmul(fact[n], invfact[r]), invfact[n-r]);
    }
}
using namespace modop;