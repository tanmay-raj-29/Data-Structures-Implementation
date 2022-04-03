vector<vector<array<int, 2>>> factors;

void factorise_all(int n) {
    factors.resize(n);
    for (int i = 2; i < n; i++) {
        if (factors[i].empty() == false) continue;
        for (int j = i; j < n; j += i) {
            int val = j, cnt = 0;
            while (val % i == 0) {
                cnt++;
                val /= i;
            }
            if (cnt) factors[j].push_back({i, cnt});
        }
    }
}