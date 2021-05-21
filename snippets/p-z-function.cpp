
vi p(string a) {
    int n = sz(a);
    vi pi(n, 0);
    rep(i,1,n) {
        int j = pi[i-1];
        while (j > 0 && a[j] != a[i]) j = pi[j-1];
        if (a[i] == a[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vi z(string a) {
    int n = sz(a);
    vi pi(n, 0);
    int l = 0, r = 0;
    rep(i,1,n) {
        if (i <= r) pi[i] = min(r-i+1, pi[i-l]);
        while (i + pi[i] < n && a[pi[i]] == a[i+pi[i]])
            pi[i] = pi[i] + 1;
        if (i + pi[i] - 1 > r) l = i, r = i + pi[i] -1;
    }
    return pi;
}
