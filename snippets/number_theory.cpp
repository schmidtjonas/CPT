// region number theory
// source: kactl
using ull = uint64_t;
ull mod_pow(ull b, ull e, ull mod) {
    ull ans = 1;
    for(; e; b = b*b % mod, e /= 2)
        if (e & 1) ans = ans*b % mod;
    return ans;
}

array<ll, 3> ext_gcd(ll a, ll b) {
    if (!b) return {a,1,0};
    auto[g, x, y] = ext_gcd(b, a % b);
    return {g, y, x - (a/b)*y};
}

bool miller_rabin(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return n - 2 < 2;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n-1), d = n >> s;
    for (auto a : A) {
        ull p = mod_pow(a, d, n), i = s;
        while (p != 1 && p != n-1 && a % n && i--) p = p*p % n;
        if (p != n-1 && i != s) return false;
    }
    return true;
}

// smallest divisors (0 for 0 and 1), list of primes O(n) runtime (from cp-algorithms.com)
pair<vector<int>, vector<int>> sieve(int n) {
    vector<int> lp(n+1, 0), pr;
    for (int64_t i = 2; i <= n; ++i) {
        if (lp[i] == 0) lp[i] = i, pr.push_back(i);
        int64_t p;
        for (int j = 0; j < pr.size() && pr[j] <= lp[i] && (p = i*pr[j]) <= n; ++j)
            lp[p] = pr[j];
    }
    return {lp, pr};
}

ull rho(ull n) {
    if (n % 2 == 0) return 2;
    auto f = [n](ull x) { return (x*x % n + 1) % n; };
    for (ull i = 2;;i++) {
        ull x = i, y = f(x), g = gcd(x - y, n);
        while (g == 1)
            x = f(x), y = f(f(y)), g = gcd(x - y, n);
        if (g != n) return g;
    }
}

vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (miller_rabin(n)) return {n};
    ull x = rho(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

vector<pair<ull, int>> factors_with_exponents(ull n) {
    auto factors = factor(n);
    sort(all(factors));
    vector<pair<ull, int>> res;
    for (auto f : factors) {
        if (res.size() && res.back().first == f) res.back().second++;
        else res.emplace_back(f, 1);
    }
    return res;
}

ull number_of_divisors(ull n) {
    auto factors = factors_with_exponents(n);
    ull ans = 1;
    for (auto[f, e] : factors) ans *= e+1;
    return ans;
}

ull sum_of_divisors(ull n) {
    auto factors = factors_with_exponents(n);
    ull ans = 1;
    for (auto[f, e] : factors) ans *= ((mod_pow(f, e+1, UINT64_MAX)-1) / (f-1));
    return ans;
}

ull totient(ull n) {
    ull ans = n;
    auto factors = factor(n);
    sort(all(factors));
    rep(i,0, factors.size()) {
        if (i == 0 || factors[i] != factors[i-1])
            ans -= ans / factors[i];
    }
    return ans;
}
// endregion
