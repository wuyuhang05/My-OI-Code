/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-16 18:05:13
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

const int MAXN = 1e5 + 5;
const int ha = 1e9 + 7;
int x[MAXN],y[MAXN];
int n,m;
P a[MAXN];
int N;
std::vector<int> S;
int f[MAXN];

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXN];

    inline void add(int pos,int d){
        while(pos < MAXN){
            (tree[pos] += d) %= ha;
            pos += lowbit(pos);
        }
    }

    inline int query(int pos){
        int res = 0;
        while(pos){
            (res += tree[pos]) %= ha;
            pos -= lowbit(pos);
        }
        return res;
    }
}bit;

inline bool cmp(P x,P y){
    return x.fi == y.fi ? x.se > y.se : x.fi < y.fi;// 同列不得转移
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",x+i);
    FOR(i,1,m) scanf("%d",y+i);
    std::sort(x+1,x+n+1);std::sort(y+1,y+m+1);
    FOR(i,1,n){
        if(x[i] <= y[1] || x[i] >= y[m]) continue;
        int p = std::lower_bound(y+1,y+m+1,x[i]) - y;
        if(x[i] == y[p]) continue;
        a[++N] = MP(x[i]-y[p-1],y[p]-x[i]);
    }
    std::sort(a+1,a+N+1,cmp);
    FOR(i,1,N) S.pb(a[i].se);
    std::sort(all(S));
    S.erase(std::unique(all(S)),S.end());
    FOR(i,1,N) a[i].se = std::lower_bound(all(S),a[i].se)-S.begin() + 2;
    f[0] = 1;
    N = std::unique(a+1,a+N+1)-a-1;
//    FOR(i,1,N) printf("%d %d\n",a[i].fi,a[i].se);
    FOR(i,1,N){
        f[i] = bit.query(a[i].se-1)+1;f[i] %= ha;
        DEBUG(f[i]);
        bit.add(a[i].se,f[i]);
    }
    int ans = 0;
    FOR(i,0,N) (ans += f[i]) %= ha;
    printf("%d\n",ans);
    return 0;
}
