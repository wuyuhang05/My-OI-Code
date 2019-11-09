/*
 * Author: RainAir
 * Time: 2019-11-08 10:19:56
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

const int MAXN = 1e6 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int du[MAXN];

inline void add(int u,int v){
    du[u]++;du[v]++;
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int n,a[MAXN];
int f[MAXN][2],ff[MAXN][2];
bool vis[MAXN],cir[MAXN];
std::vector<int> vv;

inline void topsort(){
    std::queue<int> q;
    FOR(i,1,n) if(!du[i]) q.push(i);
    while(!q.empty()){
        int v = q.front();q.pop();
        cir[v] = false;vis[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(!--du[e[i].to]) q.push(e[i].to);
        }
    }
}

std::vector<int> circle;

inline void getcircle(int v){
    int t = v,pre = 0;circle.clear();
    do{
        circle.pb(v);
        bool flag = 0,changed = 0;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == t) flag = true;
            if(e[i].to == pre) continue;
            if(!vis[e[i].to]){
                pre = v;v = e[i].to;
                vis[e[i].to] = true;
                changed = true;
                break;
            }
        }
        if(flag && !changed) vis[v] = 1,t = v;
    }while(t != v);
}

int sm,sz[MAXN],son[MAXN];
bool flag;

inline void dp1(int v,int fa=0){
    f[v][0] = 0;f[v][1] = 1;sz[v] = 1;
    int cnt = 0;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        if(cir[e[i].to]) continue;
        dp1(e[i].to,v);++cnt;
        f[v][0] += std::max(f[e[i].to][0],f[e[i].to][1]);
        f[v][1] += f[e[i].to][0];
    }
	//printf("%d:%d\n",v,cnt);
    if(!cnt && !cir[v]) sm++;
	flag &= !cnt;
	
}

inline int dp2(int n){
    FOR(i,1,n){
        ff[i][0] = std::max(ff[i][0],ff[i][0]+std::max(ff[i-1][0],ff[i-1][1]));
        ff[i][1] = std::max(ff[i][1],ff[i][1]+ff[i-1][0]);
    }
    return std::max(ff[n][0],ff[n][1]);
}

int main(){
  //  freopen("b.in","r",stdin);
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    std::fill(du+1,du+n+1,-1);
    std::fill(cir+1,cir+n+1,true);
    FOR(i,1,n) add(a[i],i);
    topsort();
//    FOR(i,1,n) DEBUG(cir[i]);
    int ans = 0,ans2 = 0;
    FOR(i,1,n){
        if(!vis[i]){
            getcircle(i);int m = circle.size();
  //          for(auto x:circle) DEBUG(x);puts("");
            flag = true;sm = 0;
            FOR(i,0,m-1){
                dp1(circle[i]);
                ff[i+1][0] = f[circle[i]][0];
                ff[i+1][1] = f[circle[i]][1];
            //    if(sz[circle[i]] != 1) flag = false;
                //sm += son[circle[i]];
            }
			//printf("%d %d %d\n",m,flag,sm);
			if(m == 1 && !sm);
            else if(flag) ans2++;
            else ans2 += sm;
            ff[1][1] = -1e9;int res = dp2(m);
            FOR(i,0,m-1){
                ff[i+1][0] = f[circle[i]][0];
                ff[i+1][1] = f[circle[i]][1];
            }
            ff[1][0] = -1e9;ff[m][1] = -1e9;
            res = std::max(res,dp2(m));
            ans += res;
        }
    }
    printf("%d %d\n",n-ans,n-ans2);
    return 0;
}

