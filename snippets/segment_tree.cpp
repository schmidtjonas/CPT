// region segtree
struct SegTree {
    struct Node {
        ll m = infl;
        ll lazy = 0;

        Node() {}
        Node(ll _val) : m(_val) {}
    };

    Node combine(Node l, Node r) {
        Node res;
        res.m = min(l.m, r.m);
        return res;
    }

    int n;
    vector<Node> t;
    explicit SegTree(const int _n) : n(_n), t(4 * _n) {}
    template<class T> explicit SegTree(const vector<T> &a) : n(a.size()), t(4 * n) { build(a, 0, 0, n); }

    static int lc(int v) { return 2*v+1; }
    static int rc(int v) { return 2*v+2; }

    template<class T> void apply(int v, T val) {
        t[v].m += val;
    }

    void push(int v) {
            if (lc(v) < t.size()) t[lc(v)].lazy += t[v].lazy, apply(lc(v), t[v].lazy);
            if (rc(v) < t.size()) t[rc(v)].lazy += t[v].lazy, apply(rc(v), t[v].lazy);
            t[v].lazy = 0;
    }

    template<class T> void build(const vector<T> &a, int v, int tl, int tr) {
        if (tr - tl == 1) t[v] = Node(a[tl]);
        else {
            int tm = (tl + tr) / 2;
            build(a, lc(v), tl, tm), build(a, rc(v), tm, tr);
            t[v] = combine(t[v*2+1], t[v*2+2]);
        }
    }

    // [l, r)
    Node query(int i) { return query(i, i+1); }
    Node query(int l, int r) { return query(0, 0, n, l, r); }
    Node query(int v, int tl, int tr, int l, int r) {
        if (l >= r) return Node();
        push(v);
        if (l == tl && r == tr) return t[v];
        int tm = (tl + tr) / 2;
        return combine(query(lc(v), tl, tm, l, min(r, tm)), query(rc(v), tm, tr, max(l, tm), r));
    }

    // set pos 0 <= p < n
    template<class T> void update(int p, T val) { update(0, 0, n, p, val); }
    template<class T> void update(int v, int tl, int tr, int p, T val) {
        if (tr - tl == 1) t[v] = Node(val);
        else {
            push(v);
            int tm = (tl + tr) / 2;
            if (p < tm) update(lc(v), tl, tm, p, val);
            else update(rc(v), tm, tr, p, val);
            t[v] = combine(t[lc(v)], t[rc(v)]);
        }
    }

    // [l, r)
    template<class T> void update(int l, int r, T val) { update(0, 0, n, l, r, val); }
    template<class T> void update(int v, int tl, int tr, int l, int r, T val) {
        if (l >= r) return;
        push(v);
        if (l == tl && r == tr) t[v].lazy += val, apply(v, val);
        else {
            int tm = (tl + tr) / 2;
            update(lc(v), tl, tm, l, min(r, tm), val), update(rc(v), tm, tr, max(l, tm), r, val);
            t[v] = combine(t[lc(v)], t[rc(v)]);
        }
    }

    /*
    // first v with query(0,v) = k or -1 if doesn't exist
    int bin_search(int k) { return bin_search(0, 0, n, k); }
    // first v with query(0,v) >= k or n if query(0,n) < k
    int lower_bound(int k) { return t[1].sum < k? n : bin_search(0, 0, n, k, false); }
    int bin_search(int v, int tl, int tr, int k, bool exact=true) {
        if (exact && k > t[v].sum) return -1;
        if (tr - tl == 1) return tl;
        int tm = (tl + tr) / 2;
        if (t[v*2+1].sum >= k) return bin_search(v*2+1, tl, tm, k);
        return bin_search(v*2+2, tm, tr, k - t[v*2+1].sum);
    }
    */
};
// for lazy: add lazy val in Node, add push method to propagate lazy, call push before recursing, add to lazy in update
// TODO change Node and methods
// endregion
