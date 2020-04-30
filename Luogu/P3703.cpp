#include<bits/stdc++.h>

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

const int MAXN = 1e5 + 5;
const int MAXM = 17;
std::vector<int> G[MAXN];
int f[MAXN],n,F[MAXN][MAXM+1];
int ch[MAXN][2],sz[MAXN],dfn[MAXN],rev[MAXN],dep[MAXN],nfd[MAXN];

struct DS{
    LL mx[MAXN<<2],tag[MAXN<<2];
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)

    inline void pushup(int x){mx[x] = std::max(mx[lc],mx[rc]);}

    inline void build(int x,int l,int r){
        mx[x] = tag[x] = 0;
        if(l == r) {mx[x] = dep[nfd[l]];return;}
        int mid = (l + r) >> 1;
        build(lc,l,mid);build(rc,mid+1,r);
        pushup(x);
    }

    inline void cover(int x,LL d){
        tag[x] += d;mx[x] += d;
    }

    inline void pushdown(int x){
        if(tag[x]){
            cover(lc,tag[x]);cover(rc,tag[x]);
            tag[x] = 0;
        }
    }

    inline void modify(int x,int l,int r,int L,int R,int d){
        if(l == L && r == R){
            cover(x,d);return;
        }
        int mid = (l + r) >> 1;pushdown(x);
        if(R <= mid) modify(lc,l,mid,L,R,d);
        else if(L > mid) modify(rc,mid+1,r,L,R,d);
        else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
        pushup(x);
    }

    inline LL query(int x,int l,int r,int L,int R){
        if(l == L && r == R) return mx[x];
        int mid = (l + r) >> 1;pushdown(x);
        if(R <= mid) return query(lc,l,mid,L,R);
        if(L > mid) return query(rc,mid+1,r,L,R);
        return std::max(query(lc,l,mid,L,mid),query(rc,mid+1,r,mid+1,R));
    }

    inline void modify(int v,int d){
        if(!v) return;
        modify(1,1,n,dfn[v],dfn[v]+sz[v]-1,d);
    }

    inline LL query(int v){
        return query(1,1,n,dfn[v],dfn[v]+sz[v]-1);
    }

    inline LL calc(int v){
        return query(1,1,n,dfn[v],dfn[v]);
    }
    #undef lc
    #undef rc
}T;
#define lc (ch[x][0])
#define rc (ch[x][1])

inline bool nroot(int x){
    return ch[f[x]][0] == x || ch[f[x]][1] == x;
}

inline void reverse(int x){
    rev[x] ^= 1;std::swap(lc,rc);
}

inline void pushdown(int x){
    if(rev[x]){
        if(lc) reverse(lc);
        if(rc) reverse(rc);
        rev[x] = 0;
    }
}
int ts;
inline void dfs(int v){
    dfn[v] = ++ts;sz[v] = 1;nfd[ts] = v;
    dep[v] = dep[f[v]]+1;F[v][0] = f[v];
    FOR(i,1,MAXM) F[v][i] = F[F[v][i-1]][i-1];
    for(auto x:G[v]){
        if(x == f[v]) continue;
        f[x] = v;dfs(x);sz[v] += sz[x];
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x]-dep[y];
        FOR(i,0,MAXM) if((d>>i)&1) x = F[x][i];
    }
    if(x == y) return x;
    ROF(i,MAXM,0){
        if(F[x][i] == F[y][i]) continue;
        x = F[x][i],y = F[y][i];
    }
    return F[x][0];
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;if(w) f[w] = y;
}

int st[MAXN];

inline void splay(int x){
    int y = x,z;
    st[z = 1] = y;
    while(nroot(y)) st[++z] = y = f[y];
    while(z) pushdown(st[z--]);
    while(nroot(x)){
        y = f[x],z = f[y];
        if(nroot(y)) rotate((ch[z][1]==y)^(ch[y][1]==x) ? x : y);
        rotate(x);
    }
}

inline int get(int x){
    if(!x) return 0;
    while(lc) x = lc;
    return x;
}

inline void access(int x){
    for(int y = 0;x;x = f[y = x]){
        splay(x);T.modify(get(rc),1);T.modify(get(y),-1);rc = y;//这里一定要获得根！！！
    }
}

int main(){int q;
    scanf("%d%d",&n,&q);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    dfs(1);
    T.build(1,1,n);
    while(q--){
        int opt,x;scanf("%d%d",&opt,&x);
        if(opt == 1){
            access(x);splay(x);
        }
        if(opt == 2){
            int y;scanf("%d",&y);
            printf("%lld\n",T.calc(x)+T.calc(y)-2*T.calc(lca(x,y))+1);
        }
        if(opt == 3){
            printf("%lld\n",T.query(x));
        }
    }
    return 0;
}
