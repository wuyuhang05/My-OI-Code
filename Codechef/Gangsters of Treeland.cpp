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

const int MAXN = 2e5 + 5;

std::vector<int> G[MAXN];
int f[MAXN],n;
int ch[MAXN][2],sz[MAXN],dfn[MAXN],rev[MAXN],dep[MAXN],nfd[MAXN];

struct DS{
    LL sm[MAXN<<2],tag[MAXN<<2];
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)

    inline void pushup(int x){sm[x] = sm[lc]+sm[rc];}

    inline void build(int x,int l,int r){
        sm[x] = tag[x] = 0;
        if(l == r) {sm[x] = dep[nfd[l]];return;}
        int mid = (l + r) >> 1;
        build(lc,l,mid);build(rc,mid+1,r);
        pushup(x);
    }

    inline void cover(int x,int l,int r,LL d){
        tag[x] += d;sm[x] += 1ll*(r-l+1)*d;
    }

    inline void pushdown(int x,int l,int r){
        if(tag[x]){
            int mid = (l + r) >> 1;
            cover(lc,l,mid,tag[x]);cover(rc,mid+1,r,tag[x]);
            tag[x] = 0;
        }
    }

    inline void modify(int x,int l,int r,int L,int R,int d){
        if(l == L && r == R){
            cover(x,l,r,d);return;
        }
        int mid = (l + r) >> 1;pushdown(x,l,r);
        if(R <= mid) modify(lc,l,mid,L,R,d);
        else if(L > mid) modify(rc,mid+1,r,L,R,d);
        else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
        pushup(x);
    }

    inline LL query(int x,int l,int r,int L,int R){
        if(l == L && r == R) return sm[x];
        int mid = (l + r) >> 1;pushdown(x,l,r);
        if(R <= mid) return query(lc,l,mid,L,R);
        if(L > mid) return query(rc,mid+1,r,L,R);
        return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
    }

    inline void modify(int v,int d){
        if(!v) return;
        modify(1,1,n,dfn[v],dfn[v]+sz[v]-1,d);
    }

    inline LL query(int v){
        return query(1,1,n,dfn[v],dfn[v]+sz[v]-1);
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
    dep[v] = dep[f[v]]+1;
    for(auto x:G[v]){
        if(x == f[v]) continue;
        f[x] = v;dfs(x);sz[v] += sz[x];
    }
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

inline void Solve(){ts=0;
    scanf("%d",&n);FOR(i,1,n) G[i].clear();
    CLR(f,0);CLR(ch,0);CLR(sz,0);CLR(dfn,0);CLR(rev,0);CLR(dep,0);CLR(nfd,0);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);++u;++v;
        G[u].pb(v);G[v].pb(u);
    }
    dfs(1);
    T.build(1,1,n);int q;scanf("%d",&q);
    while(q--){
        char str[23];int v;scanf("%s%d",str,&v);++v;
        if(str[0] == 'O'){
            access(v);
        }
        if(str[0] == 'q'){
            printf("%.10f\n",1.0*(T.query(v)-sz[v])/sz[v]);
        }
    }
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
