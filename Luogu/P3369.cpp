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
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000+5;

int N,root,tot,fa[MAXN],ch[MAXN][2],size[MAXN],cnt[MAXN],val[MAXN];

inline void pushup(int x){
    size[x] = size[ch[x][0]]+size[ch[x][1]]+cnt[x];
}

inline bool get(int x){ // 是父节点的哪里
    return x == ch[fa[x]][1];
}

inline void rotate(int x){
    int y = fa[x],z = fa[y],k = get(x);
    ch[z][get(y)] = x;fa[x] = z;
    ch[y][k] = ch[x][k^1];fa[ch[x][k^1]] = y;
    ch[x][k^1] = y;fa[y] = x;
    pushup(y);pushup(x);
}

inline void splay(int x,int v){
    int y;
    while((y = fa[x]) != v){
        int y = fa[x];
        if(fa[y] != v) rotate(get(x) == get(y) ? y : x);
        rotate(x);
    }
    if(!v) root = x;
}

void find(int x){
    if(!root) return;
    int v = root;
    while(x != val[v] && ch[v][x>val[v]]) v = ch[v][x>val[v]];
    splay(v,0);
}

int pre(int x){
    find(x);
    if(val[root] < x) return root;
    int v = ch[root][0];
    while(ch[v][1]) v = ch[v][1];
    return v;
}

int suf(int x){
    find(x);
    if(val[root] > x) return root;
    int v = ch[root][1];
    while(ch[v][0]) v = ch[v][0];
    return v;
}

int rank(int x){
    find(x);
    return size[ch[root][0]];
}

int kth(int x){
    ++x;int v = root;
    while(true){
        if(x > size[ch[v][0]]+cnt[v]) x -= size[ch[v][0]]+cnt[v],v = ch[v][1];
        else if(x <= size[ch[v][0]]) v = ch[v][0];
        else return val[v];
    }
}

void insert(int x){
    int v = root,t = 0;
    while(x != val[v] && v) t = v,v = ch[v][x>val[v]];
    if(v) ++cnt[v];
    else{
        v = ++tot;
        if(t) ch[t][x>val[t]] = v;
        ch[v][0] = ch[v][1] = 0;fa[v] = t;val[v] = x;size[v] = cnt[v] = 1;
    }
    splay(v,0);
}

void del(int x){
    int last = pre(x),next = suf(x);
    splay(last,0);splay(next,last);
    int v = ch[next][0];
    if(cnt[v] > 1) --cnt[v],splay(v,0);
    else ch[next][0] = 0;
}

int main(){
    insert(INT_MIN);insert(INT_MAX);
    scanf("%d",&N);
    while(N--){
        int opt,x;scanf("%d%d",&opt,&x);
        if(opt == 1) insert(x);
        if(opt == 2) del(x);
        if(opt == 3) printf("%d\n",rank(x));
        if(opt == 4) printf("%d\n",kth(x));
        if(opt == 5) printf("%d\n",val[pre(x)]);
        if(opt == 6) printf("%d\n",val[suf(x)]);
    }
    return 0;
}
