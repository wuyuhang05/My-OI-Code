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

int ch[MAXN][2],f[MAXN],son[MAXN],sz[MAXN];
int rev[MAXN];
// sz:所有子树
// son:虚子树
#define lc (ch[x][0])
#define rc (ch[x][1])

inline bool nroot(int x){
    return ch[f[x]][0] == x || ch[f[x]][1] == x;
}

inline void pushup(int x){
    sz[x] = sz[lc]+sz[rc]+son[x]+1;
}

inline void reverse(int x){
    std::swap(lc,rc);rev[x] ^= 1;
}

inline void pushdown(int x){
    if(rev[x]){
        if(lc) reverse(lc);
        if(rc) reverse(rc);
        rev[x] = 0;
    }
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;
    ch[x][!k] = y;f[y] = x;f[x] = z;
    ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);
}
int st[MAXN];
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
    for(int y = 0;x;x = f[y = x]){
        splay(x);son[x] += sz[rc]-sz[y];rc = y;pushup(x);
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline void link(int x,int y){
    makeroot(x);makeroot(y);f[x] = y;son[y] += sz[x];pushup(y);
}

int main(){
    int n,m;scanf("%d%d",&n,&m);std::fill(sz+1,sz+n+1,1);
    FOR(i,1,m){
        char str[23];int u,v;scanf("%s%d%d",str,&u,&v);
        if(str[0] == 'A'){
            link(u,v);
        }
        if(str[0] == 'Q'){
            makeroot(u);access(v);splay(v);//FOR(i,1,n) if(f[i] == v) DEBUG(i);
//            DEBUG(sz[u]);DEBUG(sz[v]);
            printf("%lld\n",1ll*(son[v]+1)*(sz[v]-son[v]-1));
        }
    }
    return 0;
}
