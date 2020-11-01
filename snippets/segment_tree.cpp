//region segtree
struct SegTree {
    using Node = int64_t;
    Node combine(Node l, Node r) {
        return l + r;
    }

    int n;
    vector<Node> t;
    explicit SegTree(const int _n) : n(_n), t(4 * _n) {}
    template<class T> explicit SegTree(const vector<T> &a) : n(a.size()), t(4 * n) { build(a, 1, 0, n - 1); }

    template<class T> void build(const vector<T> &a, int v, int tl, int tr) {
        if (tl == tr) t[v] = Node(a[tl]);
        else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm), build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    // [l, r]
    Node query(int l, int r) { return query(1, 0, n-1, l, r); }
    Node query(int v, int tl, int tr, int l, int r) {
        if (l > r) return Node();
        if (l == tl && r == tr) return t[v];
        int tm = (tl + tr) / 2;
        return combine(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    // set pos 0 <= p < n
    template<class T> void update(int p, T val) { update(1, 0, n-1, p, val); }
    template<class T> void update(int v, int tl, int tr, int p, T val) {
        if (tl == tr) t[v] = Node(val);
        else {
            int tm = (tl + tr) / 2;
            if (p <= tm) update(v*2, tl, tm, p, val);
            else update(v*2+1, tm+1, tr, p, val);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    // first v with query(0,v) = k or -1 if doesn't exist
    int bin_search(Node k) { return bin_search(1, 0, n-1, k); }
    // first v with query(0,v) >= k or n if query(0,n-1) < k
    int lower_bound(Node k) { return t[1] < k ? n : bin_search(1, 0, n-1, k, false); }
    int bin_search(int v, int tl, int tr, Node k, bool exact=true) {
        if (exact && k > t[v]) return -1;
        if (tl == tr) return tl;
        int tm = (tl + tr) / 2;
        if (t[v*2] >= k) return bin_search(v*2, tl, tm, k);
        return bin_search(v*2+1, tm+1, tr, k-t[v*2]);
    }
};
// for lazy: add lazy val in Node, add push method to propagate lazy, call push before recursing, add to lazy in update
// TODO change Node and methods
//endregion
