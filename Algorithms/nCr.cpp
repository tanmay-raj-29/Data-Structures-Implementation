int fact[N], invfact[N];

int pow(int a, int b, int m) {
	int ans = 1;
	while(b) {
		if(b&1)
			ans = (1ll*ans*a)%m;
		b /= 2;
		a = (1ll*a*a)%m;
	}
	return ans;
}

int modinv(int k) {
	return pow(k, MOD-2, MOD);
}

void precompute() {
	fact[0] = fact[1] = 1;
	for(int i=2; i<N; ++i) {
		fact[i] = 1ll*fact[i-1]*i%MOD;
	}
	invfact[N-1] = modinv(fact[N-1]);
	for(int i=N-2; i>=0; --i) {
		invfact[i] = 1ll*invfact[i+1]*(i+1)%MOD;
	}
}

int nCr(int x, int y) {
	return y > x ? 0 : 1ll*fact[x]*invfact[y]%MOD*invfact[x-y]%MOD;
} 