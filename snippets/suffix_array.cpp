//region suffixarray
//https://github.com/schmidtjonas/CPT
struct suffix {
    pair<int, int> parts;
    int idx;
};
struct suffarr {
    string s;
    vector<vector<int>> c;
    vector<int> sa;

    explicit suffarr(string &_s) : s(_s), sa(size(s)), c(ceil(log2(s.size() + 1)) + 1, vector<int>(s.size() + 1, 0)) { init(); }

    int operator[](size_t idx) { return sa[idx]; }

    void init() {
        string st = s + '$';
        int n = st.size();
        vector<suffix> p(n);
        for (int i = 0; i < n; i++) c[0][i] = st[i] - '$';
        for (int k = 1, gap = 1; gap < n; k++, gap *= 2) {
            for (int i = 0; i < n; i++) p[i] = {{c[k - 1][i], c[k - 1][(i + gap) % n]}, i};
            sort(p.begin(), p.end(), [](const auto &a, const auto &b) { return a.parts < b.parts; });
            for (int i = 1; i < n; i++) {
                if (p[i].parts == p[i - 1].parts) c[k][p[i].idx] = c[k][p[i - 1].idx];
                else c[k][p[i].idx] = i;
            }
        }
        for (int i = 0; i < n - 1; i++) sa[c.back()[i] - 1] = i;
    }

    int lcp(int i, int j) {
        int n = s.size() + 1, ans = 0;
        if (i == j) return n - i;
        for (int k = c.size() - 2, gap = 1 << k; k >= 0; k--, gap >>= 1)
            if (c[k][i] == c[k][j]) ans += gap, i = (i + gap) % n, j = (j + gap) % n;
        return ans;
    }
};
// O(n log^2(n)) time, O(n log(n)) space, can handle n <= 4*10^5
//endregion
