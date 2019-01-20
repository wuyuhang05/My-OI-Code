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
int N,fa[MAXN],M,a[MAXN];

inline int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

struct Node{
    int max,min;
    Node() {max = 0,min = MAXN+5;}
    Node(int x,int y) {max = x,min = y;}
}m[MAXN],ans;

struct Trie{
    int lc,rc;
    Node c;
}t[MAXN<<5];
int cnt,root;

inline int New(){
    int x = ++cnt;
    t[x].lc = t[x].rc = t[x].c.max = 0;
    t[x].c.min = MAXN;
    return x;
}

Node pushup(const Node &lc,const Node &rc){
    Node ans;
    ans.max = std::max(lc.max,rc.max);
    ans.min = std::min(lc.min,rc.min);
    return ans;
}

inline void insert(int &v,int dep,int c,int id){
    if(!v) v = New();
    t[v].c.min = std::min(t[v].c.min,id);
    t[v].c.max = std::max(t[v].c.max,id);
    if(dep < 0) return;
    if(c & (1<<dep)) insert(t[v].rc,dep-1,c,id);
    else insert(t[v].lc,dep-1,c,id);
}

inline int merge(int x,int y){
    if(!y) return x;
    if(!x) x = New();
    t[x].c = pushup(t[x].c,t[y].c);
    t[x].lc = merge(t[x].lc,t[y].lc);
    t[x].rc = merge(t[x].rc,t[y].rc);
    return x;
}

Node query(int v,int dep,int c,int id){
    if(dep < 0) return Node(0,t[v].c.min == id ? t[v].c.max : t[v].c.min);
    Node ans;
    if(c & (1<<dep))
        if(t[v].rc && (id != t[t[v].rc].c.min || id != t[t[v].rc].c.max))
            ans = query(t[v].rc,dep-1,c,id),ans.max += (1<<dep);
        else ans = query(t[v].lc,dep-1,c,id);
    else ans = query(t[v].lc,dep-1,c,id);
    return ans;
}

void dfs(int v,int dep){
    if(dep < 0) return;
    if(t[v].lc) dfs(t[v].lc,dep-1);
    if(t[v].rc) dfs(t[v].rc,dep-1);
    t[v].lc = merge(t[v].lc,t[v].rc);
}

void build(){
    cnt = 0;root = New();
    FOR(i,1,N) insert(root,M-1,a[i],find(i));
    dfs(root,M-1);
}

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N) scanf("%d",a+i),fa[i] = i;
    int now = N;LL ans = 0;
    while(now > 1){
        build();
        FOR(i,1,N) m[i] = Node(-1,0);
        FOR(i,1,N){
            Node v = query(root,M-1,a[i],find(i));
            if(v.max > m[find(i)].max) m[find(i)] = v;
        }
        FOR(i,1,N){
            if(fa[i] == i){
                int v = find(m[i].min);
                if(v != i) fa[i] = v,now--,ans += m[i].max;
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}