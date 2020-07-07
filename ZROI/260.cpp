#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int MAXN = 1e5 + 5;
const int ha = 1e9 + 7;

int n,m;

struct DS{
    int now;
    int sm[MAXN<<2],tag[MAXN<<2],ts[MAXN<<2],ori[MAXN<<2],a[MAXN];
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)
    DS(){now=1;CLR(sm,0);CLR(tag,0);CLR(ts,0);CLR(ori,0);CLR(a,0);}

    inline void clear(){now++;}

    inline void jzm(int x){
        if(ts[x] != now) ts[x] = now,sm[x] = ori[x],tag[x] = 0;
    }

    inline void build(int x,int l,int r){
        if(l == r){ori[x] = a[l];return;}
        int mid = (l + r) >> 1;
        build(lc,l,mid);build(rc,mid+1,r);
        ori[x] = (ori[lc]+ori[rc])%ha;
    }

    inline void cover(int x,int l,int r,int d){
        jzm(x);
        (sm[x] += 1ll*(r-l+1)*d%ha) %= ha;
        (tag[x] += d) %= ha;
    }

    inline void pushdown(int x,int l,int r){
        jzm(x);
        if(tag[x]){
            int mid = (l + r) >> 1;
            jzm(lc);jzm(rc);
            cover(lc,l,mid,tag[x]);
            cover(rc,mid+1,r,tag[x]);
            tag[x] = 0;
        }
    }

    inline void modify(int x,int l,int r,int L,int R,int d){
        jzm(x);jzm(lc);jzm(rc);
        if(l == L && r == R){cover(x,l,r,d);return;}
        int mid = (l + r) >> 1;pushdown(x,l,r);
        if(R <= mid) modify(lc,l,mid,L,R,d);
        else if(L > mid) modify(rc,mid+1,r,L,R,d);
        else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
        sm[x] = (sm[lc]+sm[rc])%ha;
    }

    inline int query(int x,int l,int r,int L,int R){
        jzm(x);jzm(lc);jzm(rc);
        if(l == L && r == R) {return sm[x];}
        int mid = (l + r) >> 1;pushdown(x,l,r);
        if(R <= mid) return query(lc,l,mid,L,R);
        if(L > mid) return query(rc,mid+1,r,L,R);
        return (query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R))%ha;
    }
}T1,T2;

int ans = 0;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int dep[MAXN],dfn[MAXN],fa[MAXN],tp[MAXN],sz[MAXN],son[MAXN],nfd[MAXN];
std::vector<int> G[MAXN];

inline void dfs1(int v){
    dep[v] = dep[fa[v]]+1;sz[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa[v]) continue;
        fa[e[i].to] = v;dfs1(e[i].to);
        sz[v] += sz[e[i].to];
        if(sz[e[i].to] > sz[son[v]]) son[v] = e[i].to;
    }
    (ans += 1ll*sz[v]*(n-sz[v])%ha) %= ha;
}

inline void dfs2(int v,int tp=1){
    static int ts=0;dfn[v] = ++ts;nfd[ts] = v;
    ::tp[v] = tp;
    if(son[v]) dfs2(son[v],tp);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa[v] || e[i].to == son[v]) continue;
        dfs2(e[i].to,e[i].to);
    }
}

inline void upd(int opt,int x,int d){
    if(!x) return;
    int y = 1;
    while(tp[x] != tp[y]){
        if(dep[tp[x]] < dep[tp[y]]) std::swap(x,y);
        (opt==1 ? T1:T2).modify(1,1,n,dfn[tp[x]],dfn[x],d);
        x = fa[tp[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    (opt == 1 ? T1:T2).modify(1,1,n,dfn[x],dfn[y],d);
}

inline int qry(int opt,int x){
    if(!x) return 0;
    int res = 0,y = 1;
    while(tp[x] != tp[y]){
        if(dep[tp[x]] < dep[tp[y]]) std::swap(x,y);
        (res += (opt==1 ? T1:T2).query(1,1,n,dfn[tp[x]],dfn[x]))%=ha;
        x = fa[tp[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    (res += (opt==1?T1:T2).query(1,1,n,dfn[x],dfn[y])) %= ha;
    return res;
}

int _sz[MAXN],_dep[MAXN];

inline void dfs(int v,int fa=0){
    _sz[v] = 1;_dep[v] = _dep[fa]+1;
    for(auto x:G[v]){
        if(x == fa) continue;
        dfs(x,v);_sz[v] += _sz[x];
    }
    (ans += 1ll*_sz[v]*(m-_sz[v])%ha*n%ha*n%ha) %= ha;
}

struct Node{
    int a,b,u,v;
    Node(int a=0,int b=0,int u=0,int v=0) : a(a),b(b),u(u),v(v) {}
};

std::vector<Node> event[MAXN];

int main(){
    freopen("C.in","r",stdin);
    scanf("%d%d",&n,&m);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    FOR(i,2,m){
        int a,b,u,v;scanf("%d%d%d%d",&a,&b,&u,&v);
        G[a].pb(b);G[b].pb(a);
        event[a].pb(Node(a,b,u,v));
        event[b].pb(Node(b,a,v,u));
        // ...
    }
    dfs1(1);dfs2(1);
    ans = 1ll*ans*m%ha;
    dfs(1);
    FOR(i,1,n) T1.a[i] = sz[nfd[i]],T2.a[i] = n-sz[nfd[i]];
    T1.build(1,1,n);T2.build(1,1,n);
    FOR(i,1,m){
        int t = ans;//DEBUG(i);
        for(auto x:event[i]){
//            printf("%d %d %d %d\n",x.a,x.b,x.u,x.v);
            int sz = 0;
            if(_dep[x.a] < _dep[x.b]) sz = _sz[x.b];
            else sz = m-_sz[x.a];
            sz = 1ll*sz*n%ha;
            int t1 = qry(1,x.u),t2 = qry(2,x.u);
            t1 = (T1.query(1,1,n,1,n)+ha-t1)%ha;
            (t2 += ha-T2.query(1,1,n,dfn[1],dfn[1])) %= ha;
            (ans += 1ll*t2*sz%ha) %= ha;
            (ans += 1ll*t1*sz%ha) %= ha;
            upd(1,x.u,sz);
            upd(2,x.u,ha-sz);
            T2.modify(1,1,n,1,n,sz);
//            T2.cover(1,1,n,sz);
        }
        t = (ans+ha-t)%ha;
//        DEBUG(t);
        T1.clear();T2.clear();
    }
    printf("%d\n",ans);
    return 0;
}
