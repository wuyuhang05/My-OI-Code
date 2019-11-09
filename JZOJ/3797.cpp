/*
 * Author: RainAir
 * Time: 2019-11-08 20:05:25
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

const int MAXN = 4e5 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int n,m;
LL val[MAXN];

std::vector<int> v;

namespace Subtask2{
//public:
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)
    struct Node{
        LL mx,cnt;
        
        Node(int mx=-1e9,int cnt=1) : mx(mx),cnt(cnt) {}

        inline Node operator + (const Node &t) const {
            Node res;res.mx = res.cnt = 0;
            if(mx > t.mx){
                res.mx = mx;
                res.cnt = cnt;
            }
            else if(mx < t.mx){
                res.mx = t.mx;
                res.cnt = t.cnt;
            }
            else res.mx = mx,res.cnt = cnt+t.cnt;
            return res;
        }
    }sm[MAXN<<2];

    int dfn[MAXN],nfd[MAXN],sz[MAXN],dep[MAXN],son[MAXN],tp[MAXN],fa[MAXN];

    inline void build(int x,int l,int r){
        if(l == r){
            sm[x] = Node(val[nfd[l]]-dep[nfd[l]],1);
            return;
        }
        int mid = (l + r) >> 1;
        build(lc,l,mid);build(rc,mid+1,r);
        sm[x] = sm[lc]+sm[rc];
    }

    inline void update(int x,int l,int r,int p,LL d){
        if(l == r){
            sm[x].mx = d;
            sm[x].cnt = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if(p <= mid) update(lc,l,mid,p,d);
        else update(rc,mid+1,r,p,d);
        sm[x] = sm[lc]+sm[rc];
    }

    inline Node query(int x,int l,int r,int L,int R){
        if(l == L && r == R) return sm[x];
        int mid = (l + r) >> 1;
        if(R <= mid) return query(lc,l,mid,L,R);
        if(L > mid) return query(rc,mid+1,r,L,R);
        return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
    }
/*
    inline void dfs1(int v){
        sz[v] = 1;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa[v]) continue;
            dep[e[i].to] = dep[v] + 1;
            fa[e[i].to] = v;
            dfs1(e[i].to);
            sz[v] += sz[e[i].to];
            if(sz[son[v]] < sz[e[i].to]) son[v] = e[i].to;
        }
    }*/

    std::vector<int> ce[MAXN];

    inline void dfs1(){
        std::queue<int> q;q.push(1);
        dep[1] = 1;ce[1].pb(1);int maxe = 1;
        while(!q.empty()){
            int v = q.front();q.pop();sz[v] = 1;
            for(int i = head[v];i;i = e[i].nxt){
                if(e[i].to != fa[v]){
                    dep[e[i].to] = dep[v] + 1;
                    ce[dep[e[i].to]].pb(e[i].to);
                    fa[e[i].to] = v;
                    maxe = std::max(maxe,dep[e[i].to]);
                    q.push(e[i].to);
                }
            }
        }
        int now = maxe;
        while(now){
            FOR(i,0,(int)ce[now].size()-1){
                int v = ce[now][i];
                sz[v] = 1;
                for(int i = head[v];i;i = e[i].nxt){
                    if(e[i].to == fa[v]) continue;
                    sz[v] += sz[e[i].to];
                    if(sz[e[i].to] > sz[son[v]]) son[v] = e[i].to;
                }
            }
            now--;
        }
    }
/*
    inline void dfs2(int v,int tpp=1){
        static int ts = 0;tp[v] = tpp;dfn[v] = ++ts;nfd[ts] = v;
        if(son[v]) dfs2(son[v],tpp);
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa[v] || e[i].to == son[v]) continue;
            dfs2(e[i].to,e[i].to);
        }
    }*/

    inline void dfs2(){
        static int ts = 0;
        std::stack<P> S;
        S.push(MP(1,1));
        while(!S.empty()){
            int v = S.top().fi,t = S.top().se;S.pop();
            tp[v] = t;dfn[v] = ++ts;nfd[ts] = v;
            for(int i = head[v];i;i = e[i].nxt){
                if(e[i].to != fa[v] && e[i].to != son[v]){
                    S.push(MP(e[i].to,e[i].to));
                }
            }
            if(son[v]) S.push(MP(son[v],t));
        }
    }

    inline void update(int v,int d){
        update(1,1,n,dfn[v],d-dep[v]);
    }

    inline Node query(int x,int y){
        Node res;
        while(tp[x] != tp[y]){
            if(dep[x] < dep[y]) std::swap(x,y);
            res = res+query(1,1,n,dfn[tp[x]],dfn[x]);
            x = fa[tp[x]];
        }
        if(dep[x] > dep[y]) std::swap(x,y);
        res = res+query(1,1,n,dfn[x],dfn[y]);
        return res;
    }

    inline void Solve(){
        dep[1] = 1;
        dfs1(),dfs2();
        build(1,1,n);
        FOR(i,1,m){
            int opt;scanf("%d",&opt);
            if(opt){
                int v;scanf("%d",&v);
                Node t = query(1,v);
                printf("%lld %lld\n",dep[v]+t.mx,t.cnt);
            }
            else{
                int v;LL d;scanf("%d%lld",&v,&d);
                update(v,d);
            }
        }
    }
}

int main(){
    freopen("checkin3.in","r",stdin);
    freopen("a.out","w",stdout);
    scanf("%d",&n);
    FOR(i,1,n) scanf("%lld",val+i);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    scanf("%d",&m);
    Subtask2::Solve();
    return 0;
}
