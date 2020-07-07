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

const int MAXN = 262144 + 5;
const int ha = 1e9 + 7;

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
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

int n,m,N;

struct Edge{
    int to,nxt;
}e[MAXN<<5];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}
int vis[MAXN];
int a[MAXN],b[20],c[20],ans[MAXN];
inline void Solve(){
    read(n);read(m);N = 1<<n;cnt = 0;
    FOR(i,1,N) head[i] = vis[i] = a[i] = 0;
    cnt = 0;CLR(c,0);CLR(b,0);
    FOR(i,1,m){
        int u,v;read(u);read(v);
        add(u,v);
    }
    std::queue<int> q;a[0] = 0;int t = 0,tot = 0;
    vis[1] = ++tot;
    for(int i = head[1];i;i = e[i].nxt){
        a[e[i].to] = 1<<t;++t;vis[e[i].to] = ++tot;
        q.push(e[i].to);
    }
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(vis[e[i].to] && vis[e[i].to] < vis[v]) continue;
            a[e[i].to] |= a[v];
            if(!vis[e[i].to]) vis[e[i].to] = ++tot,q.push(e[i].to);
        }
    }
    FOR(i,0,n-1) c[i] = i;
    b[0] = 1;b[n-1] = 2;ans[1] = 0;
    FOR(i,2,N){
        int x = 0;
        FOR(j,0,n-1) x |= ((a[i]>>c[j])&1)<<j;
        for(int l = 0,r = 0;l < n;l = r+1,r = l){
            if(b[l] != 1) continue;
            std::vector<int> ps;
            while(b[r] != 2 && r < n) r++;
            FOR(j,l,r) if((x>>j)&1) ps.pb(j);
            if((int)ps.size() == r-l+1 || ps.empty()) continue;
            int t = l;
            for(auto x:ps) std::swap(c[t++],c[x]);
            if(b[t] == 0) b[t] = 1;
            b[t-1] = 2;
        }
        ans[i] = 0;
        FOR(j,0,n-1) ans[i] |= ((a[i]>>c[j])&1)<<j;
    }
    int res = 0;
 //   FOR(i,1,N) DEBUG(ans[i]);
    ROF(i,N,1) res = (10ll*res%ha+ans[i])%ha;
    printf("%d\n",res);
}

int main(){
    int T;read(T);
    while(T--) Solve();
    return 0;
}
