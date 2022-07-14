int BLOCK_SIZE = 1000; // B = N ^ 2/3

struct Query {
    int L = -1, R = -1, T = 0, idx = -1;
    Query() {};
    Query(int L, int R, int T, int idx) : L(L), R(R), T(T), idx(idx) {};
    bool operator<(Query& other) const {
        return (L / BLOCK_SIZE < other.L / BLOCK_SIZE) || 
        (L / BLOCK_SIZE == other.L / BLOCK_SIZE && 
        R / BLOCK_SIZE < other.R / BLOCK_SIZE) ||
        (L / BLOCK_SIZE == other.L / BLOCK_SIZE &&
        R / BLOCK_SIZE == other.R / BLOCK_SIZE &&
        T < other.T);
    }
};

struct Update {
    int inp_vec_idx = -1, nxt = -1, prv = -1, T = -1;
    Update() {};
    Update(int inp_vec_idx, int nxt, int prv, int T) : inp_vec_idx(inp_vec_idx), nxt(nxt), prv(prv), T(T) {};
};

vector<long long> mos_algo(vector<Query>& query, vector<Update>& update, vector<int> v) {
    int sz = query.size();
    vector<long long> answer(sz);
    sort(query.begin(), query.end());
    
    // INITIALIZE DATA STRUCTURE
    
    auto add = [&] (int idx) {

    };

    auto remove = [&] (int idx) {

    }; 

    auto apply = [&] (int idx, int L, int R) {

    };

    auto undo = [&] (int idx, int L, int R) {

    };

    auto get_answer = [&] (int L, int R) -> int {
        
    };  

    int curL = 0, curR = -1, curT = 0;
    for (Query& q:query) {
        while (curT < q.T) {
            apply(curT, curL, curR);
            curT++;
        }
        while (curT > q.T) {
            curT--;
            undo(curT, curL, curR);
        }
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