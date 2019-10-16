/*
 * Author: RainAir
 * Time: 2019-10-11 11:33:33
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
const int MAXN = 100+5;
int f[MAXN][MAXN],cnt[MAXN][MAXN];
int n,m;

inline void Floyd(){
    FOR(k,1,n){
        FOR(i,1,n){
            FOR(j,1,n){
                if(f[i][j] > f[i][k] + f[k][j]){
                    f[i][j] = f[i][k] + f[k][j];
                    cnt[i][j] = cnt[i][k]*cnt[k][j];
                }
                else if(f[i][j] == f[i][k] + f[k][j])
                    cnt[i][j] += cnt[i][k]*cnt[k][j];
            }
        }
    }
}

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n) FOR(j,1,n) f[i][j] = 1e9*(i!=j);
    FOR(i,1,m){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        f[u][v] = f[v][u] = w;cnt[u][v] = cnt[v][u] = 1;
    }
    Floyd();
    FOR(i,1,n){
        double ans = 0;
        FOR(s,1,n){
            FOR(t,1,n){
                if(s == i || t == i || f[s][i]+f[i][t] != f[s][t] || s == t) continue;
                ans += 1.0*(cnt[s][i]*cnt[i][t])/cnt[s][t];
            }
        }
        printf("%.3f\n",ans);
    }
    return 0;
}
