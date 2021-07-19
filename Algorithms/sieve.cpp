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