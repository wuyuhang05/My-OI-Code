/*
 * Author: RainAir
 * Time: 2019-10-24 20:44:42
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
const int MAXN = 1e6 + 5;
const int ha = 998244353;
#define lc ((x)<<1)
#define rc ((x)<<1|1)
int w[MAXN],S,SS;

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    LL tree[MAXN];

    inline void add(int pos,int d){
        while(pos < MAXN){
            tree[pos] += d;
            pos += lowbit(pos);
        }
    }

    inline LL calc(int pos){
        LL res = 0;
        while(pos){
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
}bit[2];

int n,q;

inline LL calc(int d){
    LL ans = 0;
/*    ans = 1ll*d*query1(1,1,n,1,d);
    ans -= query2(1,1,n,1,d);
    ans += query2(1,1,n,d+1,n);
    ans -= d*query1(1,1,n,d+1,n);
    ans -= 1ll*S*d;*/
    LL gx1 = bit[0].calc(d),gx2 = bit[1].calc(d);
    ans = 1ll*d*gx1;
    ans -= gx2;
    ans += (SS-gx2);
    ans -= d*(S-gx1);
    ans -= S*d;
    return ans;
}

inline void Solve(){
    int l = 0,r = n+1,ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        int gx1 = calc(mid);
        if(gx1 >= 0) ans = mid,l = mid+1;
        else r = mid-1;
    }
//    DEBUG(ans);
//    assert(ans != -1);
    LL gx1 = bit[0].calc(ans),gx2 = bit[1].calc(ans);
    LL up = (gx2%ha-(SS-gx2)%ha+ha)%ha;
    LL down = (gx1%ha+ha-(S-gx1)%ha+ha-S)%ha;
    printf("%lld\n",1ll*up*qpow(down)%ha);
}

signed main(){
    freopen("c5.in","r",stdin);
    freopen("c.out","w",stdout);
    read(n);
    FOR(i,1,n) read(w[i]),S += w[i],SS += w[i]*i;
    FOR(i,1,n) bit[0].add(i,w[i]),bit[1].add(i,w[i]*i);
    read(q);
    FOR(i,1,q){
        int x,y;read(x);read(y);
        S -= w[x];SS -= w[x]*x;bit[0].add(x,-w[x]);bit[1].add(x,-w[x]*x);
        w[x] = y;
        S += w[x];SS += w[x]*x;bit[0].add(x,w[x]);bit[1].add(x,w[x]*x);
        Solve();
    }
    return 0;
}

