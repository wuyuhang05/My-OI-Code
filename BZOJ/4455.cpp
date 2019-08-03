/*
 * Author: RainAir
 * Time: 2019-07-30 19:16:58
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

const int MAXN = 17+2;
const int MAXM = 300+5;
int tree[MAXN][MAXN],mp[MAXN][MAXN],bk[MAXN][MAXN];
LL f[MAXN][MAXN];
int n,m;
int d[MAXN],num;

LL ans = 0;

inline int calc(int x){
    int cnt = 0;
    while(x){
        if(x%2) cnt++;
        x /= 2;
    }
    return cnt;
}

inline void dfs(int v,int fa=0){
    FOR(i,1,num) f[v][d[i]] = 1;
    //DEBUG(v);
    FOR(x,1,n){
        if(x == fa || !tree[v][x]) continue;
        //DEBUG(x);
        dfs(x,v);
        FOR(i,1,num){
          //  DEBUG(i);
            LL g = 0;
            FOR(j,1,num){
                if(mp[d[i]][d[j]]) g += f[x][d[j]];
            }
            f[v][d[i]] *= g;
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        mp[u][v] = mp[v][u] = 1;
    }
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        tree[u][v] = tree[v][u] = true;
    }
//    FOR(i,1,n) FOR(j,1,n) f[i][j] = 1;
  //  dfs(1,0);FOR(i,1,n) if(!d[i]) ans += f[1][i];
   // DEBUG(ans);
      FOR(S,0,(1<<n)-1){
        num = 0;
        FOR(i,0,n-1){
            if(!((S>>i) & 1)) d[++num] = i+1;
        }
        dfs(1,0);int sz = calc(S);
        FOR(i,1,num) ans += ((sz&1) ? -1ll : 1ll) * f[1][d[i]];
    }
    printf("%lld\n",ans);
    return 0;
}
