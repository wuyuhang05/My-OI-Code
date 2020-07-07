// start at 9:05
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

const int MAXN = 3e5 + 5;
int f[MAXN],ch[MAXN][2],rev[MAXN],sm[MAXN],sz[MAXN],val[MAXN];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
    sz[x] = sz[lc]+sz[rc]+1;
    sm[x] = sm[lc]^sm[rc]^val[x];
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
    return ch[f[x]][0]==x || ch[f[x]][1]==x;
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);if(nroot(x)) pushup(z);
}

int st[MAXN];
inline void splay(int x){
    int y,z;
    st[z = 1] = y = x;
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
    for(int y = 0;x;x = f[y=x]){
        splay(x);rc = y;pushup(x);
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline int findroot(int x){
    access(x);splay(x);pushdown(x);
    while(lc) x = lc,pushdown(x);
 //   splay(x);
    return x;
}

inline void link(int x,int y){
    makeroot(x);
    if(findroot(y) != x) f[x] = y;
}

inline void cut(int x,int y){
    makeroot(x);
    if(findroot(y) == x && f[x] == y && !rc){
        f[x] = ch[y][0] = 0;
        pushup(y);
    }
}

inline int query(int x,int y){
    makeroot(x);access(y);splay(y);
    return sm[y];
}

int n,m;

int main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",val+i),sz[i] = 1;
    FOR(i,1,m){
        int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
        if(opt == 0){
            printf("%d\n",query(x,y));
        }
        if(opt == 1){
            if(x == y) continue;
            link(x,y);
        }
        if(opt == 2){
            if(x == y) continue;
            cut(x,y);
        }
        if(opt == 3){
            splay(x);val[x] = y;pushup(x);
        }
    }
    return 0;
}
