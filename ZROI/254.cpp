// start at 8:20
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

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

const int MAXN = 2e5 + 5;

struct Node{
    int val,ps;
    Node(int val=-1e9,int ps=0) : val(val),ps(ps) {}

    bool operator < (const Node &t) const {
        if(val == t.val) return ps < t.ps;
        return val < t.val;
    }

    Node operator + (const int &d) const {
        return Node(val+d,ps);
    }
};

int f[MAXN],ch[MAXN][2],sz[MAXN],rev[MAXN];
Node ls[MAXN],rs[MAXN];
std::multiset<Node> S[MAXN];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline bool nroot(int x){
    return ch[f[x]][0]==x||ch[f[x]][1]==x;
}

inline void reverse(int x){
    rev[x] ^= 1;std::swap(lc,rc);std::swap(ls[x],rs[x]);
}

inline void pushdown(int x){
    if(rev[x]){
        if(lc) reverse(lc);
        if(rc) reverse(rc);
        rev[x] = 0;
    }
}

inline Node top(int x){
    if(S[x].empty()) return Node(-1e9,0);
    return *S[x].rbegin();
}

inline void pushup(int x){
    sz[x] = sz[lc]+sz[rc]+1;
    ls[x] = std::max(ls[lc],std::max(Node(sz[lc],x),std::max(top(x),ls[rc])+sz[lc]+1));
    rs[x] = std::max(rs[rc],std::max(Node(sz[rc],x),std::max(top(x),rs[lc])+sz[rc]+1));
    ls[x] = std::max(ls[x],Node(0,x));
    rs[x] = std::max(rs[x],Node(0,x));
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);
    if(nroot(x)) pushup(z);
}

int st[MAXN],tp;
inline void splay(int x){
    int y,z;
    st[z = 1] = y = x;
    while(nroot(y)) st[++z] = y = f[y];
    while(z) pushdown(st[z--]);
    while(nroot(x)){
        int y = f[x],z = f[y];
        if(nroot(y)) rotate((ch[z][1]==y)^(ch[y][1]==x) ? x : y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x){
    for(int y=0;x;x = f[y=x]){
        splay(x);
        if(rc) S[x].insert(ls[rc]);
        if(S[x].count(ls[y])) S[x].erase(S[x].find(ls[y]));
        rc = y;pushup(x);
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline void link(int x,int y){
    makeroot(x);makeroot(y);
    f[y] = x;S[x].insert(ls[y]);pushup(x);
}

inline void cut(int x,int y){
    makeroot(x);access(y);splay(y);ch[y][0] = f[x] = 0;
    pushup(y);
}

int n;

int main(){
    ls[0] = Node(-1e9,0);rs[0] = Node(-1e9,0);
    scanf("%d",&n);
    FOR(i,1,n) sz[i] = 1,ls[i] = rs[i] = Node(0,i);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);link(u,v);
    }
    int q;scanf("%d",&q);
    while(q--){
        int opt;scanf("%d",&opt);
        if(opt == 1){
            int u,v;scanf("%d%d",&u,&v);link(u,v);
        }
        if(opt == 2){
            int u,v;scanf("%d%d",&u,&v);cut(u,v);
        }
        if(opt == 3){
            int v;scanf("%d",&v);
            makeroot(v);Node t1 = ls[v];
            makeroot(t1.ps);Node t2 = ls[t1.ps];
            printf("%d %d\n",t1.val,t2.val);
        }
    }
    return 0;
}
