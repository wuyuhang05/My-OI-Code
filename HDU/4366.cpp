#include <unordered_map>
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
#include <assert.h>
#define fi first
#define se second
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
    #define SIZE 1000000
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}


inline void read(LL &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}


const int MAXN = 1e5 + 5;

std::vector<int> G[MAXN];
int a[MAXN],b[MAXN];
int dfn[MAXN],size[MAXN],dep[MAXN],ts=-1;

struct Node{
    int a,b,id;
    Node(){}
    Node(int a,int b,int id) : a(a),b(b),id(id) {}

    bool operator < (const Node &t) const {
        return b == t.b ? dep[id] < dep[t.id] : b > t.b;
    }
}p[MAXN];

inline void dfs(int v,int fa=-1){
    size[v] = 1;dfn[v] = ++ts;
    for(auto x:G[v]){
        if(x == fa) continue;
        dep[x] = dep[v] + 1;
        dfs(x,v);size[v] += size[x];
    }
}

#define lc (x<<1)
#define rc (x<<1|1)

int mx[MAXN<<2];

inline void pushup(int x){
    mx[x] = std::max(mx[lc],mx[rc]);
}

inline void build(int x,int l,int r){
    mx[x] = -1;//assert(l <= r);
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
}

inline void update(int x,int l,int r,int pos,int val){
//    assert(l <= r);
    if(l == r){
        mx[x] = val;return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos,val);
    else update(rc,mid+1,r,pos,val);
    pushup(x);
}

inline int query(int x,int l,int r,int L,int R){
    if(L > R) return -1;
//    assert(l <= r);
    if(l == L && r == R) return mx[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    else if(L > mid) return query(rc,mid+1,r,L,R);
    else return std::max(query(lc,l,mid,L,mid),query(rc,mid+1,r,mid+1,R));
}

int ans[MAXN],n,m,rt;
std::unordered_map<int,int> S;
// 最大化 a

inline void clear(){
    S.clear();FOR(i,0,n) ans[i] = 0;ts = -1;
    rt = 0;FOR(i,0,n) G[i].clear(),dfn[i] = size[i] = a[i] = b[i] = 0;
}

inline void Solve(){
    read(n);read(m);S[-1] = -1;
    FOR(i,1,n-1){
        int x;
        read(x);read(a[i]);read(b[i]);
        S[a[i]] = i;
        p[i] = Node(a[i],b[i],i);
        G[i].pb(x),G[x].pb(i);
        //else rt = i;
    }
    n--;
    dfs(0);build(1,1,n);
    std::sort(p+1,p+n+1);
    FOR(i,1,n){
        //if(p[i].id == 1) continue;a
     //   DEBUG(dfn[p[i].id]);DEBUG(dfn[p[i].id]+size[p[i].id]-1);
        int t = query(1,1,n,dfn[p[i].id],dfn[p[i].id]+size[p[i].id]-1);
        ans[p[i].id] = S[t];
        update(1,1,n,dfn[p[i].id],p[i].a);
    }
    while(m--){
        int x;read(x);
        printf("%d\n",ans[x]);
    }
    clear();
}

int main(){
   // freopen("big.out","r",stdin);
   // freopen("aa.out","w",stdout);
    int T;read(T);
    while(T--) Solve();
    return 0;
}
