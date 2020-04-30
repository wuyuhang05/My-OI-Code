#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define lc (ch[x][0])
#define se second
#define U unsigned
#define rc (ch[x][1])
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 100000+5;
const int ha = 51061;
int ch[MAXN][2],f[MAXN],val[MAXN],rev[MAXN],add[MAXN],mul[MAXN],size[MAXN],sum[MAXN];

bool nroot(int x){
    return ch[f[x]][0] == x || ch[f[x]][1] == x;
}

inline void reverse(int x){
    std::swap(lc,rc);rev[x] ^= 1;
}

inline void pushup(int x){
    size[x] = size[lc] + size[rc] + 1;
    sum[x] = (sum[lc] + sum[rc] + val[x])%ha;
}

inline void cover1(int x,int delta){ // add
    sum[x] += size[x] * delta;val[x] += delta;add[x] += delta;
    sum[x] %= ha;val[x] %= ha;add[x] %= ha;
}

inline void cover2(int x,int delta){
    sum[x] *= delta;val[x] *= delta;mul[x] *= delta;add[x] *= delta;
    sum[x] %= ha;val[x] %= ha;mul[x] %= ha;add[x] %= ha;
}

inline void pushdown(int x){
    if(mul[x] != 1) cover2(lc,mul[x]),cover2(rc,mul[x]);
    if(add[x]) cover1(lc,add[x]),cover1(rc,add[x]);
    if(rev[x]){
        if(lc) reverse(lc);
        if(rc) reverse(rc);
    }
    rev[x] = 0;mul[x] = 1;add[x] = 0;
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1] == x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;
    ch[x][!k] = y;ch[y][k] = w;
    if(w) f[w] = y;
    f[y] = x;f[x] = z;
    pushup(y);pushup(x);
}

int st[MAXN];

inline void splay(int x){
    int y = x,z;st[z = 1] = y;
    while(nroot(y)) st[++z] = y = f[y];
    while(z) pushdown(st[z--]);
    while(nroot(x)){
        y = f[x];z = f[y];
        if(nroot(y)) rotate((ch[y][0] == x) ^ (ch[z][0] == y) ? x : y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x){
    for(int y = 0;x;x = f[y = x]){
        splay(x);rc = y;pushup(x);
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline int findroot(int x){
    access(x);splay(x);
    while(lc) pushdown(x),x = lc;
    //splay(x);
    return x;
}

inline void split(int x,int y){
    makeroot(x);access(y);splay(y);
}

inline void link(int x,int y){
    makeroot(x);
    if(findroot(y) != x) f[x] = y;
}

inline void cut(int x,int y){
    makeroot(x);// split(x,y);
    if(findroot(y) == x && f[x] == y && !rc){
        f[x] = ch[y][0] = 0;pushup(y);
    }
}

signed main(){
    int N,M;scanf("%lld%lld",&N,&M);
    char opt[sizeof("*")+5];
    FOR(i,1,N) mul[i] = size[i] = val[i] = 1;
    FOR(i,1,N-1){
        int u,v;scanf("%lld%lld",&u,&v);
        link(u,v);
    }
    FOR(i,1,M){
        scanf("%s",opt);
        int x,y,v;
        if(opt[0] == '+'){
            scanf("%lld%lld%lld",&x,&y,&v);
            split(x,y);cover1(y,v);
        }
        if(opt[0] == '-'){
            scanf("%lld%lld",&x,&y);cut(x,y);
            scanf("%lld%lld",&x,&y);link(x,y);
        }
        if(opt[0] == '*'){
            scanf("%lld%lld%lld",&x,&y,&v);
            split(x,y);cover2(y,v);
        }
        if(opt[0] == '/'){
            scanf("%lld%lld",&x,&y);split(x,y);
            printf("%lld\n",sum[y]);
        }
    }
    return 0;
}
