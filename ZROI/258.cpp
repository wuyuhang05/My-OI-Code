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
#define P std::pair<LL,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;

int n,k,m;
int a[MAXN],b[MAXN],c[MAXN];

struct Node{
    LL sm;int ts,id;
    Node(LL sm=0,int ts=0,int id=0) : sm(sm),ts(ts),id(id) {}
    inline bool operator < (const Node &t) const {
        if(sm == t.sm) return ts > t.ts;
        return sm > t.sm;
    }
};

std::set<Node> S[MAXN];
std::map<int,P> T[MAXN];
int ans = 0,now = 0;
#include<cassert>
inline int get(int x){
    while(!S[x].empty() && (*S[x].begin()).ts <= now) S[x].erase(S[x].begin());
    if(S[x].empty()) return 0;
    return (*S[x].begin()).id;
}
bool ok[MAXN];

inline void add(int x){
    if(!ok[x]) ok[x] = 1,ans++;
}

inline void del(int x){
    if(ok[x]) ok[x] = 0,ans--;
}

inline bool pd(int x){
    if(!x) return 0;
    int t = get(x);if(!t) return 0;
//    DEBUG(x);DEBUG(t);DEBUG(S[t].size());DEBUG((*S[t].begin()).ts);DEBUG(now);
//    assert(get(t) != 0);
    return get(t)!=x;
}

inline void add(int x,int y,int d,int ts){
    int px = get(x),py = get(y);
    del(x);del(y);del(px);del(py);
    if(T[x].count(y)){
        Node p = *S[x].find(Node(T[x][y].fi,T[x][y].se,y));
        S[x].erase(p);
        p.sm += d;if(d > 0) p.ts = ts;
        if(p.sm) S[x].insert(p);
    }
    else{
        if(d) S[x].insert(Node(d,ts,y));
    }
    if(T[y].count(x)){
        Node p = *S[y].find(Node(T[y][x].fi,T[y][x].se,x));
        S[y].erase(p);
        p.sm += d;if(d > 0) p.ts = ts;
        if(p.sm) S[y].insert(p);
        assert(p.id);
    }
    else{
        if(d) S[y].insert(Node(d,ts,x));
    }
    T[x][y].fi += d;T[y][x].fi += d;
    if(d > 0) T[x][y].se = T[y][x].se = ts;
    if(!T[x][y].fi) T[x].erase(y);
    if(!T[y][x].fi) T[y].erase(x);
    int tx = get(x),ty = get(y);
    del(tx);del(ty);
    if(pd(x)) add(x);
    if(pd(y)) add(y);
    if(pd(px)) add(px);
    if(pd(py)) add(py);
    if(pd(tx)) add(tx);
    if(pd(ty)) add(ty);
}

inline void Solve(){
    scanf("%d%d%d",&n,&k,&m);ans = now = 0;
    FOR(i,1,n) S[i].clear(),ok[i] = 0,T[i].clear();
    FOR(i,1,k){
        scanf("%d%d%d",a+i,b+i,c+i);
        add(a[i],b[i],c[i],i);
        printf("%d\n",ans);
        if(i-m+1 >= 1) add(a[i-m+1],b[i-m+1],-c[i-m+1],i-m+1),now = i-m+1;
    }
}

int main(){
//    freopen("A.in","r",stdin);
//    freopen("A.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
