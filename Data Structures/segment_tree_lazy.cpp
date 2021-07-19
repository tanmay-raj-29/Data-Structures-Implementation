/*
KEYNOTES:
------------------------------------------
merge(X,id_el) = X
------------------------------------------
------------------------------------------
id_tr.combine(X) = X
------------------------------------------
------------------------------------------
ALWAYS: older_update.combine(newer_update)
------------------------------------------
*/

struct Data {
    int el = INT_MAX;
   
    Data() {};
    Data(int val) : el(val) {};
    void merge(const Data &left,const Data &right) {         
        el = min(left.el,right.el);        
    }
};

struct update {
    int v = 0; 
    
    update(){};
    update(int val) : v(val) {};
    
    void combine(update &other,const int &tl,const int &tr) {
        v += other.v;         
    }
    
    void apply(Data &x,const int &tl,const int &tr) {
        x.el += v;
        v=0;
    }
};


struct segTree {
    int len;
    vector<Data> st;
    vector<update> u;
    vector<bool> lazy;
    Data id_el;
    update id_tr;

    segTree(int l) {
        len = l;
        st.resize(4 * len);
        u.resize(4 * len);
        lazy.resize(4 * len);
        id_el = Data();
        id_tr = update();
    }
    
    void propagate(const int &node, const int &tl, const int &tr) {
        if(!lazy[node]) return;
        int tm = (tl + tr) >> 1;
        apply(node<<1,tl,tm,u[node]);
        apply(node<<1|1,tm+1,tr,u[node]);
        u[node] = id_tr;
        lazy[node] = 0;
    }
    
    void apply(const int &node, const int &tl, const int &tr, update upd) {
        if(tl != tr) {
            lazy[node] = 1;
            u[node].combine(upd,tl,tr);
        }
        upd.apply(st[node],tl,tr);
    }
    
    void build(const vector<int> &arr,const int &node, const int &tl, const int &tr) {
        if(tl == tr) {
            st[node] = arr[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build(arr,node<<1,tl,tm);
        build(arr,node<<1|1,tm+1,tr);
        st[node].merge(st[node<<1],st[node<<1|1]);
    }
    
    Data query(const int &node,const int &tl,const int &tr,const int &l,const int &r) {
        if(l > tr || r < tl) {
            return id_el;
        }
        if(tl >= l && tr <= r) {
            return st[node];
        }
        propagate(node,tl,tr);
        int tm = (tl + tr) >> 1;
        Data a = query(node<<1,tl,tm,l,r),b = query(node<<1|1,tm+1,tr,l,r),ans;
        ans.merge(a,b);
        return ans;
    }
    
    // rupd = range update
    void rupd(const int &node,const int &tl,const int &tr,const int &l,const int &r,const update &upd) {
        if(l > tr || r < tl) return;
        
        if(tl >= l && tr <= r) {
            apply(node,tl,tr,upd);
            return;
        }
        propagate(node,tl,tr);
        int tm = (tl + tr) >> 1;
        rupd(node<<1,tl,tm,l,r,upd);
        rupd(node<<1|1,tm+1,tr,l,r,upd);
        st[node].merge(st[node<<1],st[node<<1|1]);
    }
    
    void build(const vector<int> &arr) {
        build(arr,1,0,len-1);
    }
    Data query(const int &l,const int &r) {
        return query(1,0,len-1,l,r);
    }
    void rupd(const int &l,const int &r,const update &upd) {
        rupd(1,0,len-1,l,r,upd);
    }
};