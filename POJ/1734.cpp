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

const int MAXN = 100+5;
int mp[MAXN][MAXN],f[MAXN][MAXN],pre[MAXN][MAXN];
int n,m;
int ans = INT_MAX;
std::vector<int> o;

inline void upd(int i,int j,int k){
    o.clear();
    while(j != i){
        o.pb(j);j = pre[i][j];
    }
    o.pb(i);o.pb(k);
}

inline void Floyd(){
    FOR(k,1,n){
        FOR(i,1,k-1)
            FOR(j,i+1,k-1){
                if(mp[i][k] == 1e9 || mp[k][j] == 1e9 || f[i][j] == 1e9) continue;
                if(ans > f[i][j]+mp[i][k]+mp[k][j])
                    ans = std::min(ans,f[i][j]+mp[i][k]+mp[k][j]),upd(i,j,k);
            }
        FOR(i,1,n){
            FOR(j,1,n){
                if(f[i][j] > f[i][k]+f[k][j]){
                    f[i][j] = std::min(f[i][j],f[i][k]+f[k][j]);
                    pre[i][j] = pre[k][j];
                }
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,n) mp[i][j] = f[i][j] = 1e9,pre[i][j] = i;
    FOR(i,1,n) f[i][i] = 0;
    FOR(i,1,m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        mp[u][v] = mp[v][u] = w;
        f[u][v] = f[v][u] = w;
    }
    Floyd();
    if(ans == INT_MAX){
        puts("No solution.");
        return 0;
    }
    std::reverse(all(o));
    FOR(i,0,(int)o.size()-1){
        printf("%d ",o[i]);
    }
    puts("");
    
    return 0;
}
