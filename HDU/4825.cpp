/*
 * Author: RainAir
 * Time: 2019-08-25 17:13:16
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 6e6+2;

int ch[MAXN][2],tot = 1,root = 1;
LL ep[MAXN];
int n,m;
std::vector<int> dec;

inline void fg(LL x){
    dec.clear();
    FOR(i,0,32){
        dec.pb(x%2);x >>= 1;
    }
    std::reverse(all(dec));
}

inline void insert(LL t){
    fg(t);int v = root;
//    for(auto x:dec) printf("%d",x);puts("");
    for(auto x:dec){
        if(!ch[v][x]) ch[v][x] = ++tot;
        v = ch[v][x];
    }
    ep[v] = t;
}

inline LL query(LL t){
    fg(t);int v = root;
    for(auto x:dec){
        if(ch[v][!x]) v = ch[v][!x];
        else if(ch[v][x]) v = ch[v][x];
    }
    return ep[v];
}

inline void clear(){
    CLR(ch,0);tot = root = 1;CLR(ep,0);
}
int cs;
inline void Solve(){
    printf("Case #%d:\n",++cs);
    scanf("%d%d",&n,&m);
    FOR(i,1,n){
        LL x;scanf("%lld",&x);
        insert(x);
    }
    FOR(i,1,m){
        LL x;scanf("%lld",&x);
        printf("%lld\n",query(x));
    }
    clear();
}

signed main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
