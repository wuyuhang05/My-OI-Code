/*
 * Author: RainAir
 * Time: 2019-07-25 14:54:13
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

const int MAXN = 1e5 + 5;
const int ha = 1e9 + 7;
int n,m;
int f[21][MAXN];

inline int find(int i,int x){
    return x == f[i][x] ? x : f[i][x] = find(i,f[i][x]);
}

inline void merge(int p,int x,int y){ // merge([x,x+(1<<p)],[y,y+(1<<p)])
    if(find(p,x) == find(p,y)) return;
    f[p][f[p][x]] = f[p][y];
    if(!p) return;p--;
    merge(p,x,y);
    merge(p,x+(1<<p),y+(1<<p));
}

inline int calc(int x){
    int ans = 0;
    while(x){
        x /= 2;ans++;
    }
    return ans;
}

int ans;
bool vis[MAXN];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,0,20) FOR(j,1,n) f[i][j] = j;
    FOR(i,1,m){
        int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
        int lg = calc(b-a+1)-1;
        merge(lg,a,c);merge(lg,b-(1<<lg)+1,d-(1<<lg)+1);
    }ans = 9;vis[find(0,1)] = true;
    FOR(i,2,n){
        int t = find(0,i);
        if(!vis[t]) vis[t] = true,ans = 1ll*ans*10%ha;
    }
    printf("%d\n",ans);
    return 0;
}
