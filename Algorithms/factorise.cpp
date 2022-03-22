const int NUM = 1e5+5;
bool prime[NUM];

void sieve() {
    memset(prime,true,sizeof(prime));
    prime[0]=false;
    prime[1]=false;
    for(int i = 2; i*i < NUM; ++i) {
        if(prime[i]) { 
            for(int j = i*i; j < NUM; j+=i) {
                prime[j] = false;
            }
        }
    }
}

vector<array<int, 2>> factorise(int x) {
    if (prime[2] == false) sieve();
    vector<array<int, 2>> factors;
    for (int i = 2; i < NUM && x > 1; ++i) {
        if (prime[i] == false) continue;
        int cnt = 0;
        while (x % i == 0) {
            cnt++;
            x /= i;
        }
        if (cnt > 0) factors.push_back({i, cnt});
        if (prime[x]) {
            factors.push_back({x, 1});
            break;
        }
    }
    return factors;
}