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
const int MAXN = 30+5;

int p[MAXN],cnt,pw[MAXN];

inline void calc(int x){
    cnt = 0;CLR(p,0);
    if(!x) p[cnt++] = 0;
    while(x) p[cnt++] = x%10,x /= 10;
}

int f[MAXN][12][2];

inline int dfs(int pos,int pre,int fg,int lim){
    if(pos == -1) return fg;
    if(!lim && f[pos][pre][fg] != -1) return f[pos][pre][fg];
    int res = 0,ed = (lim ? p[pos] : 9);
    FOR(i,0,ed){
        res += dfs(pos-1,i,fg || (i == 9 && pre == 4),lim&&i == ed);
    }
    if(!lim) f[pos][pre][fg] = res;
 //   printf("%lld %lld %lld %lld\n",pos,pre4,lim,res);
  //  if(!lim) f[pos][pre4] = res;
    return res;
}

inline int solve(int x){
    calc(x);
    return dfs(cnt-1,0,0,1);
}

signed main(){
    int T;scanf("%lld",&T);CLR(f,-1);
    pw[0] = 1;FOR(i,1,18) pw[i] = pw[i-1]*10;
    while(T--){
        int x;scanf("%lld",&x);
        printf("%lld\n",solve(x));
    }
    return 0;
}
