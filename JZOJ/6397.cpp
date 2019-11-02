/*
 * Author: RainAir
 * Time: 2019-10-31 20:14:04
 */
#pragma GCC optimize("Ofast")
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 6000+5;
const int MAXM = 13;

int a[MAXN],b[MAXN];
int ri[MAXN][MAXN]; // i right to j
int mn[MAXN][MAXM+1],ps[MAXN][MAXM+1];
int n;
int stk[MAXN],pc[MAXN];

inline void prework(){
    FOR(i,1,MAXM){
        for(int j = 0;j + (1<<(i-1)) < MAXN;++j){
            if(mn[j][i-1] < mn[j+(1<<(i-1))][i-1])
                mn[j][i] = mn[j][i-1],ps[j][i] = ps[j][i-1];
            else
                mn[j][i] = mn[j+(1<<(i-1))][i-1],ps[j][i] = ps[j+(1<<(i-1))][i-1];
        }
    }
}

inline int calc(int l,int r){
    if(!l) ++l;
    int c = pc[r-l+1]-1;
    if(mn[l][c] < mn[r-(1<<c)+1][c]) return ps[l][c];
    else return ps[r-(1<<c)+1][c];
}

int dis[MAXN],f[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline void Union(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return;
    f[fy] = fx;
}

int cnt;
std::queue<int> q[MAXN+233];

inline void bfs(int s){
//    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    FOR(i,0,n+5) f[i] = i;
//    FOR(i,s,n) q.push(MP(dis[i],i));
    FOR(i,s,n) q[dis[i]].push(i);
    FOR(i,0,n+5){
        while(!q[i].empty()){
        int v = q[i].front();q[i].pop();
        int l = a[v],r = find(v-1);
        while(l <= r && r){
            if(dis[r] > dis[v] + 1){
                dis[r] = dis[v] + 1;
                q[dis[r]].push(r);
            }
            if(r == 1) break;
            Union(r-1,r);
            r = find(r);
        }
    }
}}

int main(){
//    freopen("traffic.in","r",stdin);
//    freopen("traffic.out","w",stdout);
    freopen("3.in","r",stdin);
    scanf("%d",&n);
    FOR(i,1,MAXN-1) pc[i] = pc[i>>1]+1;
    FOR(i,2,n) scanf("%d",a+i);
    FOR(i,2,n) scanf("%d",b+i),mn[i][0] = b[i],ps[i][0] = i;
    prework();
    FOR(i,1,n) FOR(j,1,n) ri[i][j] = 1e9;
    ri[1][1] = 0;
    FOR(j,2,n){
        ri[j][j] = 0;
        ROF(i,j-1,1){
            if(i >= b[j]) ri[i][j] = 1;
            else ri[i][j] = ri[i][calc(b[j],j-1)] + 1;
        }
    }
    int ans = 0;
    FOR(i,1,n){
        FOR(j,1,n) dis[j] = ri[i][j];
        bfs(i);
        FOR(j,1,n) ans ^= (i+j)*dis[j];
    }
    printf("%d\n",ans);
    return 0;
}
