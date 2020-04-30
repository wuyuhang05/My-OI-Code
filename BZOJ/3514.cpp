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
int n,m,k,type;

int f[MAXN<<1],ch[MAXN<<1][2],mn[MAXN<<1],ps[MAXN<<1],val[MAXN<<1],rev[MAXN<<1];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
    ps[x] = x;mn[x] = val[x];
    if(mn[lc] < mn[x]) mn[x] = mn[lc],ps[x] = ps[lc];
    if(mn[rc] < mn[x]) mn[x] = mn[rc],ps[x] = ps[rc];
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

inline bool nroot(int x){
    return ch[f[x]][0] == x || ch[f[x]][1] == x;
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);
}

int st[MAXN<<1];

inline void splay(int x){
    int y = x,z;st[z = 1] = y;
    while(nroot(y)) st[++z] = y = f[y];
    while(z) pushdown(st[z--]);
    while(nroot(x)){
        y = f[x],z = f[y];
        if(nroot(y)) rotate((ch[z][1]==y)^(ch[y][1]==x)?x:y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x){
    for(int y=0;x;x = f[y = x]){
        splay(x);rc = y;pushup(x);
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline int find(int x){
    access(x);splay(x);while(lc) pushdown(x),x = lc;return x;
}

inline void split(int x,int y){
    makeroot(x);access(y);splay(y);
}

inline void link(int x,int y){
    makeroot(x);makeroot(y);f[x] = y;
}

inline void cut(int x,int y){
    split(x,y);ch[y][0] = f[x] = 0;pushup(y);
}

int pre[MAXN];

P edge[MAXN];
int root[MAXN],sm[MAXN<<5],ls[MAXN<<5],rs[MAXN<<5],tot;

inline void insert(int prev,int &v,int l,int r,int p){
    sm[v = ++tot] = sm[prev]+1;ls[v] = ls[prev];rs[v] = rs[prev];
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid) insert(ls[prev],ls[v],l,mid,p);
    else insert(rs[prev],rs[v],mid+1,r,p);
}

inline int query(int x,int y,int l,int r,int L,int R){
    if(l == L && r == R) return sm[y]-sm[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(ls[x],ls[y],l,mid,L,R);
    if(L > mid) return query(rs[x],rs[y],mid+1,r,L,R);
    return query(ls[x],ls[y],l,mid,L,mid)+query(rs[x],rs[y],mid+1,r,mid+1,R);
}

inline void dfs(int x){
    if(lc) dfs(x);
    printf("%d ",x);
    if(rc) dfs(rc);
}

int main(){
    scanf("%d%d%d%d",&n,&m,&k,&type);FOR(i,0,n) ps[i] = i,val[i] = mn[i] = 1e9;
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);edge[i] = MP(u,v);val[n+i] = i;ps[n+i] = n+i;
        if(u == v){
            pre[i] = i;continue;
        }
        if(find(u) == find(v)){
            split(u,v);int t = ps[v];//DEBUG(val[v]);
            cut(edge[t-n].fi,t);cut(t,edge[t-n].se);
            pre[i] = t-n;
        }
        link(u,n+i);link(n+i,v);
    }
    FOR(i,1,m) insert(root[i-1],root[i],0,m,pre[i]);int lst = 0;
    while(k--){
        int l,r;scanf("%d%d",&l,&r);
        if(type) l ^= lst,r ^= lst;
        printf("%d\n",lst = n-query(root[l-1],root[r],0,m,0,l-1));
    }
    return 0;
}
