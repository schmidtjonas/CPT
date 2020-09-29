#import<iostream>
int p[1<<22],r,i,j;
int main() {
    std::string n,m;
    std::cin >> n >> m;
    for(n = m+'0'+n; i < size(n); r+= (p[i] = j + (n[i]==n[j])) == size(m))
        for(j = p[i++]; j && n[i]-n[j]; j = p[j-1]);
    std::cout << r;
}