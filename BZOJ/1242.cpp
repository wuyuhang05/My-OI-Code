/*
 * Time: 2019-11-26 13:10:02
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

const int MAXN = 1000+5;
const int MAXM = MAXN*MAXN;

struct Edge{
    int to,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;
bool con[MAXN][MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
    con[u][v] = con[v][u] = 1;
}

struct Node{
    int id;
    Node *pre,*suf;
    
    inline void del(){
        pre->suf = suf;
        if(suf) suf->pre = pre;
    }

    inline void insert(Node *p){
        p->pre = this;
        p->suf = suf;
        if(suf) suf->pre = p;
        suf = p;
    }
}h[MAXN],p[MAXN];

int ans[MAXN],pos[MAXN],ts[MAXN];
bool vis[MAXN];
int n,m;
inline void build(){
    FOR(i,1,n) p[i].id = i;
    FOR(i,1,n) h[0].insert(&p[i]);
    int mx = 0;
    ROF(i,n,1){
        while(h[mx+1].suf) ++mx;
        while(mx && !h[mx].suf) --mx;
        int v = h[mx].suf->id;h[mx].suf->del();
        ans[i] = v;pos[v] = i;vis[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(!vis[e[i].to]){
                p[e[i].to].del();
                h[++ts[e[i].to]].insert(&p[e[i].to]);
            }
        }
    }
}

inline bool check(){
    ROF(k,n,1){
        int v = ans[k];std::vector<int> t;
        for(int i = head[v];i;i = e[i].nxt){
            if(pos[e[i].to] > k){
                t.pb(e[i].to);
            }
        }
        if(!t.empty()) FOR(i,1,(int)t.size()-1) if(!con[t[0]][t[i]]) return false;
    }
    return true;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    build();
    puts(check() ? "Perfect" : "Imperfect");
    return 0;
}
