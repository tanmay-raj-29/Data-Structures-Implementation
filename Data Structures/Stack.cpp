template <typename T>
struct Stack {
    vector<T> v, mn, mx;

    Stack() {
        mn.push_back(INF);
        mx.push_back(-INF);
    }

    void push(T el) {
        v.push_back(el);
        mn.push_back(min(mn.back(), el));
        mx.push_back(max(mx.back(), el));
    }

    T pop() {
        T val = v.back();
        v.pop_back();
        mn.pop_back();
        mx.pop_back();
        return val;
    }

    bool empty() {
        return v.empty();
    }

    T get_min() {
        return mn.back();
    }

    T get_max() {
        return mx.back();
    }
};