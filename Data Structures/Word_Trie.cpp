
struct Trie {
    static const int LEN = 26;
    struct node {
        node* nxt[LEN];
        int sz;
        node() {
            for (int i = 0; i < LEN; i++) {
                nxt[i] = NULL;
            }
            sz = 0;
        }
    } *root;
    Trie() {
        root = new node();
    }
    void insert(string& s) {
        node* cur = root;
        cur -> sz++;
        for (char& c:s) {
            int b = (c - 'a');
            if (cur -> nxt[b] == NULL) {
                cur -> nxt[b] = new node();
            }
            cur = cur -> nxt[b];
            cur -> sz++;
        }
    }
    int query(string& s) { // check if s exists in trie
        node* cur = root;
        int ans = 0;
        for (char& c:s) {
            if (cur == NULL) break;
            int b = (c - 'a');
            cur = cur -> nxt[b];
            ans += cur->sz;
        }
        return ans;
    }
    void del(node* cur) {
        for (int i = 0; i < 2; i++) {
            if (cur -> nxt[i]) {
                del(cur -> nxt[i]);
            }
        }
        delete(cur);
    }
};
