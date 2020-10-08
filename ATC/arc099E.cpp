/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-17 07:32:01
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

const int MAXN = 700+5;
int mp[MAXN][MAXN];
int n,m;
bool vis[MAXN];
int col[MAXN];
int a[MAXN],b[MAXN],tot;
int f[MAXN][MAXN];
//std::vector<int> pt;
bool flag = true;

inline void dfs(int v){
 //   pt.pb(v);
    FOR(x,1,n){
        if(!mp[v][x]) continue;
        if(!vis[x]){
            vis[x] = true;
            col[x] = 3-col[v];dfs(x);
        }
        else if(col[v] == col[x]) flag = false;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,n) mp[i][j] = (i != j);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        mp[u][v] = mp[v][u] = 0;
    }
    FOR(i,1,n){
        if(!vis[i]){
            CLR(col,0);
            col[i] = 1;dfs(i);
            if(!flag){
                puts("-1");
                return 0;
            }
            int cnt1 = 0,cnt2 = 0;
            FOR(i,1,n){
                if(col[i] == 1) ++cnt1;
                else if(col[i] == 2) ++cnt2;
            }
            a[++tot] = cnt1;b[tot] = cnt2;
        }
    }
    f[0][0] = 1;
//    DEBUG(a[tot]);DEBUG(b[tot]);
    FOR(i,1,tot){
        ROF(j,n,0){
            ROF(k,n,0){
                if(j >= a[i] && k >= b[i]) f[j][k] |= f[j-a[i]][k-b[i]];
                if(j >= b[i] && k >= a[i]) f[j][k] |= f[j-b[i]][k-a[i]];
            }
        }
    }
    int ans = 1e9;
    FOR(i,0,n){
        if(f[i][n-i]) ans = std::min(ans,i*(i-1)/2+(n-i)*(n-i-1)/2);
    }
    printf("%d\n",ans);
    return 0;
}
