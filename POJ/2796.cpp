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

const int MAXN = 100000+5;
int n;
int l[MAXN],r[MAXN],val[MAXN],f[MAXN],pos;
int stk[MAXN],tp,rt;
LL size[MAXN];
LL ans = 0ll;

inline void build(int n){
    stk[tp=0] = 1;
    FOR(i,2,n){
        while(tp >= 0 && val[stk[tp]] >= val[i]) tp--;
        if(tp > -1){
            f[i] = stk[tp];
            f[r[stk[tp]]] = i;
            //f[i] = stk[tp];
            l[i] = r[stk[tp]];
            r[stk[tp]] = i;
        }
        else{
            f[stk[0]] = i;l[i] = stk[0];
        }
        stk[++tp] = i;
    }
    FOR(i,1,n)
        if(!f[i]){rt = i;return;}
}

inline void dfs(int v){
    size[v] = val[v];
    if(l[v]) dfs(l[v]);
    if(r[v]) dfs(r[v]);
    size[v] += size[l[v]] + size[r[v]];
    if(ans < 1ll*size[v]*val[v]){
        ans = 1ll*size[v]*val[v];
        pos = v;
    }
}

inline void init(){
    CLR(l,0);CLR(r,0);CLR(val,0);CLR(f,0);CLR(size,0);CLR(stk,0);tp = rt = 0;ans = 0;
}

inline void Solve(){
    init();
    FOR(i,1,n) scanf("%d",val+i);
    if(n == 1){
        printf("%d\n%d %d\n",val[1],1,1);return;
    }
    build(n);ans = INT_MIN;dfs(rt);
    int t = pos,la = t,ra = t;
    while(l[la]) la = l[la];
    while(r[ra]) ra = r[ra];
    printf("%lld\n",ans);
    printf("%d %d\n",la,ra);
}

int main(){
    scanf("%d",&n);Solve();
    return 0;
}


