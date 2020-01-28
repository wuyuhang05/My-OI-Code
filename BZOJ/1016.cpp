/*
 * Time: 2019-11-29 21:12:04
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 2000+5;
const int ha = 31011;

struct Edge{
    int u,v,w;

    bool operator < (const Edge &t) const {
        return w < t.w;
    }
}e[MAXN<<1];

int n,m;
int f[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline bool merge(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return false;
    f[fy] = fx;return true;
}

bool tag[MAXN];

inline int get(int lim){
    FOR(i,1,n) f[i] = i;int ans = 0;
    int cnt = 0;
    FOR(i,1,m) if(tag[i]){
        ans += e[i].w;
        if(!merge(e[i].u,e[i].v)) return 1e9;
        ++cnt;
    }
    FOR(i,1,m){
        if(e[i].w == lim) continue;
        int fu = find(e[i].u),fv = find(e[i].v);
        if(fu == fv) continue;
        ++cnt;
        merge(e[i].u,e[i].v);ans += e[i].w;
    }
    if(cnt != n-1){
        if(lim == -233){
            puts("0");
            exit(0);
        }
        else{
            return 1e9;
        }
    }
    return ans;
}

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,m) scanf("%lld%lld%lld",&e[i].u,&e[i].v,&e[i].w);
    std::sort(e+1,e+m+1);
    int base = get(-233),ans = 1;
    for(int l = 1,r;l <= m && r <= m;l = r+1){
        r = l;
        while(e[r+1].w == e[l].w) ++r;
        int sz = r-l+1,tot = 0;
        FOR(S,0,(1<<sz)-1){
            FOR(i,0,sz-1){
                if((1<<i)&S) tag[l+i] = 1;
            }
          //  FOR(i,1,n) printf("%d ",tag[i]);puts("");
            if(get(e[l].w) == base) tot++;
          ///  DEBUG(get(e[l].w));
            FOR(i,l,r) tag[i] = 0;
        }
        //DEBUG(tot);
        ans = 1ll*ans*tot%ha;
    }
    printf("%lld\n",ans);
    return 0;
}
