#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 1e5 + 5;
const int ha = 998244353;

inline void add(int &a,int b){
    a += b;if(a >= ha) a -= ha;
}

std::vector<int> G[MAXN];
int f[MAXN][3][3][3];

inline void dfs(int v){
    int now[3][3][3],t[3][3][3],res[3][3][3];
    bool flag = true;CLR(now,0);
    for(auto to:G[v]){
        dfs(to);
        if(flag){
            FOR(i,0,2) FOR(j,0,2) FOR(k,0,2) now[(3-i)%3][j][k] = f[to][i][j][k];
            flag = false;
            // 预处理第一个叶子和根节点的合并。
        }
        else{
            FOR(i,0,2) FOR(j,0,2) FOR(k,0,2) t[(3-i)%3][j][k] = f[to][i][j][k];
            CLR(res,0);
            FOR(ix,0,2) FOR(jx,0,2) FOR(kx,0,2) FOR(iy,0,2-ix)
                for(Re int jy = 0;jy <= 2 && kx+jy <= 3;++jy)
                    FOR(ky,0,2)
                        if(!(kx+jy) || kx+jy == 3) add(res[ix+iy][jx][ky],1ll*now[ix][jx][kx]*t[iy][jy][ky]%ha);
            memcpy(now,res,sizeof(res));
        }
    }
    if(flag){
        FOR(i,0,2) FOR(j,0,2-i) FOR(k,0,2-i-j)
            f[v][i][j][k] = (i+j+k != 1);
    }
    else{
        FOR(i,0,2) FOR(j,0,2) FOR(k,0,2){
            int t = now[i][j][k];
            add(f[v][2-i][j][k],t);
            if(!i) add(f[v][0][j][k],t);
        }
    }
}

int n;

int main(){
    scanf("%d",&n);
    FOR(i,2,n){
        int x;scanf("%d",&x);
        G[x].pb(i);
    }
    dfs(1);
    int ans = 0;
    FOR(i,0,2) add(ans,f[1][0][i][(3-i)%3]);
    printf("%d\n",ans);
    return 0;
}
