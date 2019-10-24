/*
 * Author: RainAir
 * Time: 2019-10-24 08:21:15
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
const int MAXN = 2000000+5;
LL f[MAXN];
int a[MAXN],sm[MAXN];
int n;LL m;

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    LL tree[MAXN];

    inline void add(int pos,LL x){
        pos = std::min(pos,MAXN-1);
        if(pos <= 0) return;
        while(pos){
            tree[pos] = std::max(tree[pos],x);
            pos -= lowbit(pos);
        }
    }

    inline LL query(int pos){
        LL res = LLONG_MIN;
        while(pos < MAXN){
            res = std::max(res,tree[pos]);
            pos += lowbit(pos);
        }
        return res;
    }
}bit;

signed main(){
    //freopen("C.in","r",stdin);
  //  int tt = sizeof(bit)+sizeof(sm);
  //  DEBUG(tt/1024);
    scanf("%lld%lld",&n,&m);
    FOR(i,0,MAXN-1) bit.tree[i] = LLONG_MIN;
    FOR(i,1,n) scanf("%lld",sm+i);
    FOR(i,1,n) sm[i] += sm[i-1];
    f[0] = m;
    bit.add(f[0]/100,f[0]-sm[0]);
    FOR(i,1,n){
        LL mx = 0;
        /*FOR(j,0,i-1){
            if(f[j] >= 100*i) mx = std::max(mx,f[j]-sm[j]);
        }*/
        mx = bit.query(i);
        f[i] = mx+sm[i]-100*i;
        bit.add(f[i]/(100),f[i]-sm[i]);
    }
    printf("%lld\n",f[n]);
    return 0;
}

