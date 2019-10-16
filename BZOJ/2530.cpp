/*
 * Author: RainAir
 * Time: 2019-10-12 14:29:40
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

const int MAXN = 3000+5;
int mp[MAXN][MAXN],du[MAXN],p[MAXN];
bool vis[MAXN];
int n,m;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,n) mp[i][j] = i!=j;
    FOR(i,1,n) du[i] = n-1,p[i] = i;
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        mp[u][v] = mp[v][u] = 0;--du[u];--du[v];
    }
    FOR(i,1,n/3){
        int mn = 1e9,ps = 0;
        FOR(j,1,n) if(!vis[j]){
            if(du[j] < mn) mn = du[j],ps = j;
        }
        printf("%d ",ps);vis[ps] = true;
        FOR(i,1,n) if(mp[ps][i]) vis[i] = true;
    }
    puts("");
    return 0;
}
