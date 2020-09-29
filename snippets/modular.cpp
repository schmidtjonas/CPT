//region modular
template<class M>
struct Modular {
    using I = decltype(M::m());
    using Mul = uint64_t;
    I val = 0;
    static constexpr I m() { return M::m(); }

    constexpr Modular() = default;
    template<class T> constexpr Modular(T _val) { _val %= M::m(); if (_val < 0) _val += M::m(); val = static_cast<I>(_val); }

    template<class T> constexpr explicit operator T() const { return static_cast<T>(val); }
#define DEFINE_OP(op) constexpr auto operator op(Modular o) const { return val op o.val; }
    DEFINE_OP(==) DEFINE_OP(!=) DEFINE_OP(<) DEFINE_OP(<=) DEFINE_OP(>) DEFINE_OP(>=) DEFINE_OP(%) DEFINE_OP(&) DEFINE_OP(^) DEFINE_OP(|) DEFINE_OP(<<) DEFINE_OP(>>)
#undef DEFINE_OP

    constexpr Modular& operator+=(Modular o) { if ((val += o.val) >= M::m()) val -= M::m(); return *this; }
    constexpr Modular& operator-=(Modular o) { if (val < o.val) val += M::m(); val -= o.val; return *this; }
    template<class T> constexpr Modular& operator+=(T r) { return *this += Modular(r); }
    template<class T> constexpr Modular& operator-=(T r) { return *this -= Modular(r); }
    constexpr Modular operator+(Modular o) const { return Modular(*this) += o; }
    constexpr Modular operator-(Modular o) const { return Modular(*this) -= o; }
    constexpr Modular& operator++() { return *this += 1; }
    constexpr Modular& operator--() { return *this -= 1; }
    constexpr Modular operator++(int) { auto r = *this; *this += 1; return r; }
    constexpr Modular operator--(int) { auto r = *this; *this -= 1; return r; }
    constexpr Modular operator+() const { return *this; }
    constexpr Modular operator-() const { return Modular(-val + M::m()); }

    constexpr Modular operator*(Modular o) const { return Modular(static_cast<Mul>(*this) * static_cast<Mul>(o)); }
    constexpr Modular& operator*=(Modular o) { return *this = *this * o; }
    template<class T> constexpr Modular& operator*=(T o) { return *this *= Modular(o); }

    template<class T> constexpr Modular pow(T e) const { Modular a = 1, b = *this; for (; e > 0; b *= b, e /= 2) if (e % 2) a *= b; return a; }
    constexpr Modular inv() const { return this->pow(M::m() - 2); }

    constexpr Modular& operator/=(Modular o) { return *this = *this * o.inv(); }
    constexpr Modular operator/(Modular o) const { return Modular(*this) /= o; }
    template <class T> constexpr Modular operator/=(T r) { return *this /= Modular(r); }
};
#define DEFINE_OPS(op) \
    template <class M, class T, class = enable_if_t<is_integral<T>::value>> constexpr auto operator op(Modular<M> l, T r) { return Modular<M>(l) op Modular<M>(r); } \
    template <class M, class T, class = enable_if_t<is_integral<T>::value>> constexpr auto operator op(T l, Modular<M> r) { return Modular<M>(l) op Modular<M>(r); }
DEFINE_OPS(==) DEFINE_OPS(!=) DEFINE_OPS(<) DEFINE_OPS(<=) DEFINE_OPS(>) DEFINE_OPS(>=) DEFINE_OPS(+) DEFINE_OPS(-)
DEFINE_OPS(*) DEFINE_OPS(/) DEFINE_OPS(%) DEFINE_OPS(&) DEFINE_OPS(^) DEFINE_OPS(|) DEFINE_OPS(<<) DEFINE_OPS(>>)
#undef DEFINE_OPS
template<class M> std::ostream& operator<<(std::ostream& out, Modular<M> m) { return out << m.val; }
template<class M> std::istream& operator>>(std::istream& in, Modular<M>& m) { ll val; in >> val; m = Modular<M>(val); return in; }
template<class M> string to_string(Modular<M> m) { return ::to_string(m.val); }
namespace std { template<class M> struct hash<Modular<M>> { size_t operator()(Modular<M> m) const { return hash<typename Modular<M>::I>()(m.val); } }; }

// ToDo change modulo, check overflow for input and *
template<class I, I M> struct Mod { static constexpr I m() { return M; } };
using mi = Modular<Mod<int, (int)1e9 + 7>>;
using vmi = vector<mi>;
//endregion
