/*
 * Author: RainAir
 * Time: 2019-11-07 14:32:26
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
int n;
P a[MAXN];
int w[MAXN],lim[MAXN];

inline bool cmp(const P &a,const P &b){
    return a.fi == b.fi ? a.se > b.se : a.fi > b.fi;
}

inline void clear(){
    FOR(i,1,n) lim[i] = 0;
}

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXN];
    inline void clear(){
        CLR(tree,0);
    }

    inline void add(int pos,int x){
        while(pos){
            tree[pos] = std::max(tree[pos],x);
            pos -= lowbit(pos);
        }
    }

    inline int query(int pos){
        int res = 0;
        while(pos < MAXN){
            res = std::max(res,tree[pos]);
            pos += lowbit(pos);
        }
        return res;
    }
}bit;

std::vector<int> S;
int f[MAXN];

inline void Solve(){
    bit.clear();
    scanf("%d",&n);S.clear();
    FOR(i,1,n) scanf("%d%d",&a[i].fi,&a[i].se),S.pb(a[i].se);
    std::sort(all(S));
    S.erase(std::unique(all(S)),S.end());
    FOR(i,1,n) a[i].se = std::lower_bound(all(S),a[i].se)-S.begin()+1;
    std::sort(a+1,a+n+1,cmp);
    int m;scanf("%d",&m);
    FOR(i,1,m) scanf("%d",w+i);
    std::sort(w+1,w+m+1);
    int now = m;
    FOR(i,1,n){
        while(now && w[now] >= a[i].fi) now--;
        lim[i] = m-now;
    }
    int ans = 0;
    FOR(i,1,n){
        f[i] = std::min(lim[i],bit.query(a[i].se)+1);
        bit.add(a[i].se,f[i]);
        ans = std::max(ans,f[i]);
    }
    printf("%d\n",ans);
    clear();
}

int main(){
    freopen("bag10.in","r",stdin);
//    freopen("bag.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
