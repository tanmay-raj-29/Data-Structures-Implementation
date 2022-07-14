const int NUM = 1e5 + 5;
bool prime[NUM];
vector<int> pr;

void linear_sieve() {
    memset(prime, true, sizeof prime);
    
    for (int i = 2; i < NUM; i++) {
        if (prime[i]) pr.push_back(i);
        for (int j = 0; j < (int)pr.size() && i * prime[j] < NUM; j++) {
            prime[i * prime[j]] = false;

            if (i % prime[j] == 0) break;
        }
    }
}