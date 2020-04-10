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
#define int LL
const int MAXN = 1e5 + 5;

int sz[MAXN],mx[MAXN],val[MAXN],tag[MAXN],rev[MAXN],f[MAXN],tot;
int ch[MAXN][2];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
    mx[x] = std::max(val[x],std::max(mx[lc],mx[rc]));
    sz[x] = sz[lc]+sz[rc]+1;
}

inline void reverse(int x){
    rev[x] ^= 1;std::swap(lc,rc);
}

inline void cover(int x,int d){
    mx[x] += d;val[x] += d;tag[x] += d;
}

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

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;f[w] = y;
    pushup(y);pushup(x);
}

int st[MAXN],rt;

inline void splay(int x,int v=0){
    int y = x,z = 0;
    st[z = 1] = y;
    while(f[y] != v) st[++z] = y = f[y];
    while(z) pushdown(sz[z--]);
    while((y = f[x]) != v){
        if((z = f[y]) != v) rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
        rotate(x);
    }
    if(!v) rt = x;
    pushup(x);
}

inline int getkth(int k){
    int x = rt;
    while(true){
        pushdown(x);
        if(k <= sz[lc]) x = lc;
        else if(k == sz[lc]+1) {splay(x);return x;}
        else k -= sz[lc]+1,x = rc;
    }
    return -1;
}

inline int split(int l,int r){
    l = getkth(l-1);r = getkth(r+1);
    splay(l,0);splay(r,l);
    return ch[r][0];
}

inline void build(int f,int &x,int l,int r){
    if(l > r) return;
    x = (l+r)>>1;;::f[x] = f;sz[x] = 1;
    if(l == r) return;
    build(x,lc,l,x-1);build(x,rc,x+1,r);
    pushup(x);
}
int n,m;
inline void dfs(int x){
    pushdown(x);
    if(lc) dfs(lc);
//    if(2 <= x && x <= n+1)printf("%d ",x-1);
    if(rc) dfs(rc);
}

signed main(){
    mx[0] = -1e18;
    scanf("%lld%lld",&n,&m);
    build(0,rt,1,n+2);
    FOR(i,1,m){
        int opt;scanf("%lld",&opt);int l,r;scanf("%lld%lld",&l,&r);++l;++r;
        int v = split(l,r);
        if(opt == 1){
            int d;scanf("%lld",&d);
            cover(v,d);
        }
        if(opt == 2){
            reverse(v);
        }
        if(opt == 3){
            printf("%lld\n",mx[v]);
        }
     //   dfs(rt);
//        FOR(i,2,n+1) DEBUG(val[i]);
    }
    return 0;
}
