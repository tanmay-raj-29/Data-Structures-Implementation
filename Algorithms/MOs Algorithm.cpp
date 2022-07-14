int BLOCK_SIZE = 1000;

struct Query {
    int L = -1, R = -1, idx = -1;
    Query() {};
    Query(int L, int R, int idx) : L(L), R(R), idx(idx) {};
    bool operator<(Query& other) const {
        return (L / BLOCK_SIZE < other.L / BLOCK_SIZE) || 
        (L / BLOCK_SIZE == other.L / BLOCK_SIZE && 
        (L / BLOCK_SIZE % 2 ? 
        R / BLOCK_SIZE < other.R / BLOCK_SIZE : 
        R / BLOCK_SIZE > other.R / BLOCK_SIZE));
    }
};

int square_root(int v) {
    int L = 1, R = v, opt = L;
    while (L <= R) {
        int mid = L + (R - L) / 2;
        if (1LL * mid * mid <= v) {
            L = mid + 1;
            opt = mid;
        }
        else {
            R = mid - 1;
        }
    }
    return opt;
}

vector<int> mos_algo(vector<Query>& query, vector<int>& v) {
    int n = (int)v.size();
    BLOCK_SIZE = square_root(n);
    int sz = query.size();
    vector<int> answer(sz);
    sort(query.begin(), query.end());
    
    // INITIALIZE DATA STRUCTURE
    
    auto add = [&] (int idx) {

    };

    auto remove = [&] (int idx) {
    
    }; 

    auto get_answer = [&] (int L, int R) -> int {
        
    };  

    int curL = 0, curR = -1;
    for (Query& q:query) {
        while (curL > q.L) {
            curL--;
            add(curL);
        }
        while (curR < q.R) {
            curR++;
            add(curR);
        }
        while (curL < q.L) {
            remove(curL);
            curL++;
        }
        while (curR > q.R) {
            remove(curR);
            curR--;
        }
        answer[q.idx] = get_answer(curL, curR);
    }
    return answer;
}