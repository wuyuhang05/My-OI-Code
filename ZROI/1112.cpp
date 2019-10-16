/*
 * Author: RainAir
 * Time: 2019-10-05 16:43:35
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
const int MAXN = 1e5 + 5;
const int MAXL = 19;

const int _[10][4] = {
    {},
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {2,0,0,0},
    {0,0,1,0},
    {1,1,0,0},
    {0,0,0,1},
    {3,0,0,0},
    {0,2,0,0},
};

LL S[MAXN];int cnt;
bool vis[MAXL*3][MAXL*2][MAXL+1][MAXL+1];

inline void dfs(int step,int v,int e1,int e2,int e3,int e4,LL x){
    if(step == 19){
        if(vis[e1][e2][e3][e4]) return;
        vis[e1][e2][e3][e4] = true;
        S[++cnt] = x;
        return;
    }
    for(;v <= 9;++v) dfs(step+1,v,e1+_[v][0],e2+_[v][1],e3+_[v][2],e4+_[v][3],x*v);
}

int to[MAXN][10];
int f[MAXL+1][MAXN][10];
//  考虑到前 i 位，乘积为 j(-> <= j )，该为为 k(-> <= k)

inline void prework(){
    dfs(1,1,0,0,0,0,1);
    std::sort(S+1,S+cnt+1);
    FOR(i,1,9){
        int k = 0;
        FOR(j,1,cnt){
            LL t = i*S[j];
            while(k <= cnt && S[k] != t) ++k;
            to[j][i] = k;
        }
    }
    FOR(i,1,9) f[1][i][i] = 1;
    FOR(i,1,MAXL-1){
        FOR(j,1,cnt){
            FOR(k,1,9){
                FOR(x,1,9){
                  //  DEBUG(to[j][x]);
                    f[i+1][to[j][x]][x] += f[i][j][k];
                }
            }
        }
    }
    FOR(i,1,MAXL){
        FOR(j,1,cnt){
            FOR(k,1,9){
                f[i][j][k] += f[i][j][k-1];
            }
        }
    }
    FOR(i,1,MAXL){
        FOR(j,1,cnt){
            FOR(k,1,9){
                f[i][j][k] += f[i][j-1][k];
            }
        }
    }
}

std::vector<int> dec;

inline int _calc(int len,int fs,int p){
   // DEBUG(p);
    int k = std::lower_bound(S+1,S+cnt+1,p)-S;
   // DEBUG(S[k]);
    return f[len][k][fs];
}

inline int query(int len,int fs,int l,int r){
    DEBUG(_calc(len,fs,r));DEBUG(_calc(len,fs,l));
    return _calc(len,fs,r)-_calc(len,fs,l);
}

inline int calc(LL x,LL l,LL r){
    dec.clear();
    while(x) dec.pb(x%10),x /= 10;
    std::reverse(all(dec));DEBUG(dec.size());
    int len = dec.size(),ans = 0;
    FOR(i,1,len-1) ans += query(i,9,l,r);
    int lst = 0;
    FOR(i,0,len-1){
        if(!dec[i]) break;
        if(dec[i] > 1) ans += query(len,dec[i]-1,l,r);
        l /= dec[i];r /= dec[i];
        lst = i;
    }
    if(!lst && !l && r) ++ans;// 0
    return ans;
}

signed main(){
    int T;scanf("%lld",&T);
    prework();
    FOR(i,1,T){
        int L,R,l,r;scanf("%lld%lld%lld%lld",&L,&R,&l,&r);
        printf("%lld\n",calc(R,l-1,r)-calc(L-1,l-1,r));
    }
    return 0;
}
