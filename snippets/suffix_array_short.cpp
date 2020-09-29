//
// Suffix array shorter implementation
//

#include <bits/stdc++.h>

#define rep0(a, b)  for(int a = 0; a < (b); ++a)
#define rep1(a, b)  for(int a = 1; a < (b); ++a)
#define trav(a, b)  for(auto& a : (b))
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'
#define INF         0x3f3f3f3f
#define M           1000000009 // fix construction against 31 and 10e9+7

using namespace std;
using vvi = vector<vector<int>>;
using vi = vector<int>;
using ll = int64_t;

struct substr {
    pair<int, int> parts;
    int ind;
};

int lcp(int i, int j, int n, vector<vector<int>>& c) {
    int ans = 0;
    if (i == j) return n - i;
    for (int k = c.size()-2, gap = 1 << k; k >= 0; k--, gap >>= 1) {
        if (c[k][i] == c[k][j]) {
            ans += gap;
            i = (i + gap) % n;
            j = (j + gap) % n;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    cin >> s;
    s += '$';
    int n = s.size();

    vector<vector<int>> c(ceil(log2(n)) + 1, vector<int>(n, 0));
    vector<substr> p(n);
    for (int i = 0; i < n; i++) c[0][i] = s[i] - '$';

    for (int k = 1, gap = 1; gap < n; k++, gap *= 2) {
        for (int i = 0; i < n; i++)
            p[i] = {{c[k - 1][i], c[k - 1][(i + gap) % n]}, i};

        sort(all(p), [](auto &&a, auto &&b) {return a.parts < b.parts;});

        for (int i = 1; i < n; i++) {
            if (p[i].parts == p[i - 1].parts)
                c[k][p[i].ind] = c[k][p[i - 1].ind];
            else
                c[k][p[i].ind] = i;
        }
    }
    vector<int> sa (n-1);
    rep0(i,n-1) sa[c[c.size() - 1][i] - 1] = i;

    rep0(i,n-1) cout << sa[i] << ' ';
    cout << endl;
    rep1(i,n-1)
        cout << lcp(sa[i], sa[i-1], n, c) << ' ';

    return 0;
}
