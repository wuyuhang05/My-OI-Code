#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

std::map<std::string,int> S;
std::map<int,std::string> rS;
int cnt;

inline int calc(const std::string &str){
    if(S[str]) return S[str];
    S[str] = ++cnt;
    rS[cnt] = str;
    return cnt;
}

int N;
const int MAXN = 100000+5;

int f[MAXN];

inline void pre(){
    FOR(i,1,MAXN-2) f[i] = i;
}

int find(int x){
    // return f[x] == x ? x : f[x] = find(f[x]);
    int r = x;
    while(r != f[r]) r = f[r];
    int v = x;
    while(v != r){
        int t = f[v];
        f[v] = r;
        v = t;
    }
    return r;
}
std::string str1,str2;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin >> N;pre();
    FOR(i,1,N){
        int opt,u,v;
        std::cin >> opt >> str1 >> str2;
        u = calc(str1);v = calc(str2);
        int fu = find(u),fv = find(v);
        if(!opt) f[fu] = fv;
        else puts(fu==fv ? "yes" : "no");
    }
    system("pause");
    return 0;
}