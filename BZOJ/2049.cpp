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

#define Re register
#define LL long long
#define U unsigned
#define lc c[x][0]
#define rc c[x][1]
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;

int c[MAXN][2],f[MAXN],tag[MAXN];

inline void reverse(int x){
    std::swap(lc,rc);
    tag[x] ^= 1;
}

inline void pushdown(int x){
    if(tag[x]){
        reverse(lc);reverse(rc);
        tag[x] = 0;
    }
}

inline bool nroot(int x){
    return c[f[x]][0] == x || c[f[x]][1] == x;
}

inline void rotate(int x){
    int y = f[x],z = f[y];
    int k = c[y][1] == x,w = c[x][!k]; // k=1
    if(nroot(y)) c[z][c[z][1]==y] = x;
    c[x][!k] = y;c[y][k] = w;
    if(w) f[w] = y;f[y] = x;f[x] = z;
}
int st[MAXN];
inline void splay(int x){
    int y=x,z;st[z=1]=y;
    while(nroot(y)) st[++z] = y = f[y];
    while(z) pushdown(st[z++]);
    while(nroot(x)){
        y = f[x],z = f[y];
        if(nroot(y)) rotate((c[y][0] == x) ^ (c[z][0] == y) ? x : y);
        rotate(x);
    }
    // pushup(x);
}

inline void access(int x){
    for(int y = 0;x;x = f[y = x]){
        splay(x);rc = y;
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline int findroot(int x){
    access(x);splay(x);
    while(lc) pushdown(x),x=lc;
    return x;
}



int main(){
    return 0;
}