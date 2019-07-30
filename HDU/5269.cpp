/*
 * Author: RainAir
 * Time: 2019-07-27 19:48:37
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
#define int LL
const int MAXN = 1e6 + 5;
const int ha = 998244353;
int a[MAXN],n;
std::vector<int> bit[MAXN];

int ch[MAXN][2],tag[MAXN];
int rt = 1,cnt = 1;
int lg = 0;

inline void add(int ttt){
    int v = rt;
    for(auto x:bit[ttt]){
        if(!ch[v][x]) ch[v][x] = ++cnt;
        v = ch[v][x];tag[v]++;
    }
}

inline int query(int ttt){
    int v = rt;LL base = 1;LL ans = 0;
    for(auto x:bit[ttt]){
        if(ch[v][!x]){
            (ans += base*tag[ch[v][!x]]%ha)%=ha;
        }
        v = ch[v][x];base <<= 1;
    }
    return ans;
}

inline int cal(int x){
    int res = 1;
    while(x){
        x /= 2;res++;
    }
    return res;
}

inline void Solve(int _){
    scanf("%lld",&n);CLR(ch,0);CLR(tag,0);cnt = 1;rt = 1;lg = 30;
    FOR(i,1,n) scanf("%lld",a+i),bit[i].clear();
    int ans = 0;
    FOR(i,1,n){
        int t = a[i];
        FOR(sb,1,lg){
            bit[i].pb(t%2);
            t /= 2;
        }
        add(i);
        (ans += query(i)) %= ha;
    }
    printf("Case #%lld: %lld\n",_,1ll*ans*2%ha);
}

signed main(){
  //  freopen("test.in","r",stdin);
    int T;scanf("%lld",&T);
    FOR(i,1,T) Solve(i);
    return 0;
}
