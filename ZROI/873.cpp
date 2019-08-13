/*
 * Author: RainAir
 * Time: 2019-08-04 19:05:58
 */
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <unordered_map>
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e6 + 5;
int n,m;

inline char nc(){
    #define SIZE 200000+1
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

struct Edge{
    int to,nxt,id,id2;
}e[MAXN<<1];
int cnt,head[MAXN],du[MAXN];
int dep[MAXN];
bool vis[MAXN],used[MAXN];

inline void init(){
    FOR(i,0,n) head[i] = 0,vis[i] = 0;
    cnt = 1;
}

inline void add(int u,int v,int id,int id2=0,int type=0){
    e[++cnt] = (Edge){v,head[u],id,id2};head[u] = cnt;
    if(!type) e[++cnt] = (Edge){u,head[v],id,id2};
    else e[++cnt] = (Edge){u,head[v],id2,id};head[v] = cnt;
}
int f[MAXN];
std::vector<std::pair<P,P> > adds;

inline void dfs(int v,int faid=0,int fa=0){
    int tof = 0;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || vis[e[i].to]) continue;
        dep[e[i].to] = dep[v] + 1;f[e[i].to] = v;
        vis[e[i].to] = true;dfs(e[i].to,e[i].id,v);
    }
    int lst = 0,lstid;
    for(int i = head[v];i;i = e[i].nxt){
        if(dep[e[i].to] > dep[v]){
              if(!used[e[i].to] || f[e[i].to] != v){
                if(!lst) lst = e[i].to,lstid = e[i].id;
                else adds.pb(MP(MP(lst,e[i].to),MP(lstid,e[i].id))),lst = 0;
              }
        }
    }
    if(lst) adds.pb(MP(MP(lst,fa),MP(lstid,faid))),used[v] = true;
}

std::vector<P> ans;

inline void euler(int v){
    for(int i = head[v];i;i = head[v]){
        head[v] = e[head[v]].nxt;
        if(!vis[i]){
            vis[i] = vis[i^1] = 1;
            euler(e[i].to);
            ans.pb(MP(e[i].id,e[i].id2));
        }
    }
}

std::vector<P> t;

int main(){
    read(n);read(m);
    FOR(i,1,m){
        int u,v;//scanf("%d%d",&u,&v);
        read(u);read(v);
        ++du[u];++du[v];
        add(u,v,i);
    }
    if(m & 1){
        puts("0");return 0;
    }
    FOR(i,1,n) if(!(du[i]&1)){
        puts("0");return 0;
    }puts("1");
    vis[1] = dep[1] = 1;dfs(1,0);init();
    for(auto x:adds){
        add(x.fi.fi,x.fi.se,x.se.fi,x.se.se,1);
    }
    FOR(i,1,n) add(0,i,i,0,1);
    euler(0);
 //   if(n == 49996)assert(false);
    //ROF(i,(int)ans.size()-1,0) printf("%d %d\n",ans[i].fi,ans[i].se);
    ROF(i,(int)ans.size()-1,0){
        auto x=ans[i];
        if(x.fi == 0){
            if(t.empty()) continue;
            printf("%d ",(int)t.size()*2);
            for(auto xx:t) printf("%d %d ",xx.fi,xx.se);puts("");
            t.clear();
        }
        else if(x.se) t.pb(x);
    }
    if(!t.empty()){
        printf("%d ",(int)t.size());
        for(auto xx:t) printf("%d %d ",xx.fi,xx.se);puts("");
    }
    return 0;
}
