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

const int MAXN = 200000+5;

int ch[MAXN][2],tag[MAXN],size[MAXN],val[MAXN],f[MAXN];

bool nroot(int x){
    return ch[f[x]][0] == x || ch[f[x]][1] == x;
}

inline void reverse(int x){
    std::swap(lc,rc);tag[x] ^= 1;
}

inline void pushdown(int x){
    if(tag[x]){
        if(lc) reverse(lc);
        if(rc) reverse(rc);
        tag[x] = 0;
    }
}

inline void pushup(int x){
    size[x] = 1;
    if(lc) size[x] += size[lc];
    if(rc) size[x] += size[rc];
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;
    ch[x][!k] = y;ch[y][k] = w;
    if(w) f[w] = y;
    f[y] = x;f[x] = z;
    pushup(y);
}

int st[MAXN];
inline void splay(int x){
    int y = x,z;st[z = 1] = y;
    while(nroot(y)) st[++z] = y = f[y];
    while(z) pushdown(st[z--]);
    while(nroot(x)){
        y = f[x];z = f[y];
        if(nroot(y)) rotate((ch[y][0]==x)^(ch[z][0]==y) ? x : y);
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
    splay(x);
    return x;
}

inline void link(int x,int y){
    makeroot(x);
    if(findroot(y) != x) f[x] = y;
}

inline void cut(int x,int y){
    makeroot(x);access(y);splay(y);
    f[x] = ch[y][0] = 0;pushup(y);
}

inline int calc(int x,int y){
    makeroot(x);access(y);splay(y);
    return size[y];
}

int main(){
    int N,M;scanf("%d",&N);
    FOR(i,1,N+1) size[i] = 1;
    int T = N+1;
    FOR(i,1,N){
        scanf("%d",val+i);
        if(i+val[i] <= N) link(i,i+val[i]);
        else link(i,T);
    }
    scanf("%d",&M);
    while(M--){
        int opt,x,y;scanf("%d%d",&opt,&x);x++;
        if(opt == 1){
            printf("%d\n",calc(x,T)-1);
        }
        else{
            scanf("%d",&y);cut(x,x+val[x]<=N?x+val[x]:T);
            link(x,x+y<=N?x+y:T);
            val[x] = y;
        }
    }
    return 0;
}