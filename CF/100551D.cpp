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

struct LCT{
    int ch[MAXN][2],f[MAXN],mn[MAXN],cnt[MAXN],rev[MAXN],val[MAXN],tag[MAXN];
    #define lc (ch[x][0])
    #define rc (ch[x][1])

    inline bool nroot(int x){return (ch[f[x]][0]==x)||(ch[f[x]][1]==x);}
    inline void reverse(int x){rev[x] ^= 1;std::swap(lc,rc);}
    inline void cover(int x,int d){mn[x] += d;val[x] += d;tag[x] += d;}
    inline void pushdown(int x){
        if(rev[x]){
            if(lc) reverse(lc);
            if(rc) reverse(rc);
            rev[x] = 0;
        }
        if(tag[x]){
            if(lc) cover(lc,tag[x]);
            if(rc) cover(rc,tag[x]);
            tag[x] = 0;
        }
    }

    inline void pushup(int x){
        mn[x] = val[x];cnt[x] = 1;
        if(mn[lc] < mn[x]) mn[x] = mn[lc],cnt[x] = cnt[lc];
        else if(mn[lc] == mn[x]) cnt[x] += cnt[lc];
        if(mn[rc] < mn[x]) mn[x] = mn[rc],cnt[x] = cnt[rc];
        else if(mn[rc] == mn[x]) cnt[x] += cnt[rc];
    }

    inline void rotate(int x){
        int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
        if(nroot(y)) ch[z][ch[z][1]==y] = x;f[x] = z;
        ch[x][!k] = y;f[y] = x;ch[y][k] = w;if(w) f[w] = y;
        pushup(y);pushup(x);
    }
    int st[MAXN];
    inline void splay(int x){
        int y=x,z;st[z=1]=y;
        while(nroot(y)) st[++z] = y = f[y];
        while(z) pushdown(st[z--]);
        while(nroot(x)){
            y = f[x];z = f[y];
            if(nroot(y)) rotate((ch[z][1]==y)^(ch[y][1]==x) ? x : y);
            rotate(x);
        }
        pushup(x);
    }

    inline void access(int x){
        for(int y=0;x;x = f[y = x]){
            splay(x);rc = y;pushup(x);
        }
    }

    inline void makeroot(int x){access(x);splay(x);reverse(x);}
    inline void split(int x,int y){makeroot(x);access(y);splay(y);}
    inline int findroot(int x){access(x);splay(x);while(lc) pushdown(x),x = lc;splay(x);return x;}
    inline void link(int x,int y){makeroot(x);makeroot(y);f[x] = y;}
    inline void cut(int x,int y){split(x,y);f[x] = ch[y][0] = 0;pushup(y);}
    inline void modify(int x,int y,int d){split(x,y);cover(y,d);}
    #undef lc
    #undef rc
}T;

struct Node{
    int u,v,id;
    bool use;
    Node(int u = 0,int v = 0,int id=0,bool use=0) : u(u),v(v),id(id),use(use) {}
};

std::vector<Node> G[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void modify(int x,int l,int r,int L,int R,Node d){
    if(l == L && r == R) {G[x].pb(d);return;}
    int mid = (l + r) >> 1;
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
}

int ans[MAXN],now;

inline void dfs(int x){
    if(T.ch[x][0]) dfs(T.ch[x][0]);
//    DEBUG(x);DEBUG(T.val[x]);
    if(T.ch[x][1]) dfs(T.ch[x][1]);
}

inline void work(int x,int l,int r){
    int tmp = now;
//    if(l == 19 && r == 20) DEBUG(now);
    for(auto &e:G[x]){
//        if(e.u == 4 && e.v == 7) DEBUG(l),DEBUG(r);
      //  if(l == 19 && r == 20) DEBUG(e.u),DEBUG(e.v);
        if(T.findroot(e.u) == T.findroot(e.v)){
      //      if(l == 19 && r == 20) DEBUG(e.u),DEBUG(e.v);
            T.split(e.u,e.v);
    //        if(l == 19 && r == 20)DEBUG(T.mn[e.v]),dfs(e.v);
            if(!T.mn[e.v]) now -= T.cnt[e.v];
            T.cover(e.v,1);
        }
        else{
            T.val[e.id] = T.mn[e.id] = T.rev[e.id] = T.tag[e.id] = 0;T.cnt[e.id] = 1;
            T.link(e.u,e.id);T.link(e.id,e.v);e.use = 1;++now;
        }
    }
    if(l == r) ans[l] = now;
    if(l != r){
        int mid = (l + r) >> 1;
        work(lc,l,mid);work(rc,mid+1,r);
    }
    now = tmp;
    std::reverse(all(G[x]));
//    DEBUG(G[x].size());
    for(auto e:G[x]){
        if(e.use){
            T.cut(e.u,e.id);T.cut(e.id,e.v);
        }
        else{
            T.modify(e.u,e.v,-1);
        }
    }
}

int n,m;
std::map<P,int> S;
int tot = 0;

int main(){
#ifndef RainAir
    freopen("bridges3.in","r",stdin);
    freopen("bridges3.out","w",stdout);
#endif
    scanf("%d%d",&n,&m);tot = n;std::fill(T.val,T.val+n+1,1e9);T.mn[0] = 1e9;
    FOR(i,1,m){
        char opt[23];int u,v;scanf("%s%d%d",opt,&u,&v);if(u > v) std::swap(u,v);
        if(opt[0] == 'A'){
            S[MP(u,v)] = i;
        }
        if(opt[0] == 'D'){
            modify(1,1,m,S[MP(u,v)],i-1,Node(u,v,++tot));
            S.erase(S.find(MP(u,v)));
        }
    }
    for(auto x:S) modify(1,1,m,x.se,m,Node(x.fi.fi,x.fi.se,++tot));
    work(1,1,m);
    FOR(i,1,m) printf("%d\n",ans[i]);
    return 0;
}


