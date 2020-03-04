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
#define lc child[x][0]
#define rc child[x][1]
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 300000+5;
int f[MAXN],child[MAXN][2],val[MAXN],s[MAXN],tag[MAXN];
bool r[MAXN];

inline bool nroot(int x){
    return child[f[x]][0] == x || child[f[x]][1] == x;
}

inline void pushup(int x){
    s[x] = s[lc]^s[rc]^val[x];
}

inline void reverse(int x){
    int t = lc;lc = rc;rc = t;tag[x] ^= 1;
}

inline void pushdown(int x){
    if(tag[x]){
        if(lc) reverse(lc);
        if(rc) reverse(rc);
        tag[x] = 0;
    }
}

inline void rotate(int x){
    int y = f[x],z = f[y];int k = child[y][1]==x,w = child[x][!k];
    if(nroot(y)) child[z][child[z][1]==y] = x;
    child[x][!k] = y;child[y][k] = w;
    if(w) f[w] = y;
    f[y] = x,f[x] = z;
    pushup(y);
}
int st[MAXN];
inline void splay(int x){
    int y = x,z;st[z = 1] = y;
    // std::stack<int> S;
    // S.push(y);
    while(nroot(y)) st[++z] = y = f[y];//S.push(y=f[y]);
    while(z) pushdown(st[z--]);
    //while(!S.empty()) pushdown(S.top()),S.pop();
    while(nroot(x)){
        y = f[x];z = f[y];
        if(nroot(y)) rotate((child[y][0] == x) ^ (child[z][0] == y) ? x : y);
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
	// splay(v);  某势能分析指出这一句话是要加来保证复杂度的，但是不加貌似没错.....
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
    makeroot(x);
    if(findroot(y) == x && f[x] == y && !rc){
        f[x] = child[y][0] = 0;
        pushup(y);
    }
}

int N,M;

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N) scanf("%d",val+i);
    FOR(i,1,M){
        int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
        if(opt == 0) split(x,y),printf("%d\n",s[y]);
        if(opt == 1) link(x,y);
        if(opt == 2) cut(x,y);
        if(opt == 3) splay(x),val[x] = y;
    }
    return 0;
}