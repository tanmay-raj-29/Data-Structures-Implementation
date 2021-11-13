#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 2e5+5;
const int maxa = 1e6+5;

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3):((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2*pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}
struct query{
    int l,r,id;
    int64_t ord;
    inline void calcOrder() {
        ord = gilbertOrder(l, r, 21, 0);
    }
}qry[maxn];
inline bool operator<(const query &a, const query &b) {
    return a.ord < b.ord;
}
bool vis[maxn];
vector<ll> freq(maxa);
int cnt=0;
ll arr[maxn];
ll ans[maxn];
struct mo{
    ll res;
    int cl,cr;
    void setup(){
        res=0;
        for(int i=0;i<maxn;i++) vis[i] = 0;
        for(int i=0;i<maxa;i++) freq[i] = 0;
    }
    inline void add(int i){
        res -= freq[i]*freq[i]*i;
        freq[i]++;
        res += freq[i]*freq[i]*i;
    }
    inline void remove(int i){
        res -= freq[i]*freq[i]*i;
        freq[i]--;
        res += freq[i]*freq[i]*i;
    }
    void compute(int m){
        setup();
        cl = qry[0].l , cr = qry[0].l-1 ;
        for(int i=0;i<m;i++){
            while( cr < qry[i].r ) add(arr[++cr]);
            while( cr > qry[i].r ) remove(arr[cr--]);
            while( cl < qry[i].l ) remove(arr[cl++]);
            while( cl > qry[i].l ) add(arr[--cl]);
            ans[qry[i].id] = res;
        }
        for(int i=0;i<m;i++){
            cout<<ans[i]<<"\n";
        }
    }
}mo_algo;
 
int main(){
    int n,t;
    cin >> n >> t;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    for(int i=0;i<t;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        qry[i].l=l;
        qry[i].r=r;
        qry[i].id=i;
        qry[i].calcOrder();
    }
    sort(qry,qry+t);
    mo_algo.compute(t);
}
