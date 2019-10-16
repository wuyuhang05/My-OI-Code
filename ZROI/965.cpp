/*
 * Author: RainAir
 * Time: 2019-09-26 20:24:20
 */
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

#define fi first
#define se second
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

const int MAXN = 4000+5;
const int INF = 0x3f3f3f3f;
int a[MAXN],b[MAXN];
std::vector<std::pair<P,int> > _; // 无意义的东西不需要名字
int X,n;
//std::unordered_map<LL,int> f[MAXN],tp[MAXN];
//std::unordered_map<LL,P> pre[MAXN];
//std::unordered_map<LL,P> S[MAXN];
P S[MAXN][2*MAXN];
//std::unordered_map<LL,bool> vis[MAXN];
int f[MAXN][2*MAXN],tp[MAXN][2*MAXN];
P pre[MAXN][2*MAXN];
bool vis[MAXN][2*MAXN];
/*
inline LL calc(const P &x){
    LL res = x.fi*19260817ll+x.se;
    S[res] = x;
    return res;
}
*/
inline int calc(int i,const P &x){
    int res = 0;
    if(!x.fi) res = MAXN+x.se;
    else res = x.fi;
//    if(S[i].count(res)){
//        if(S[i][res] != x) printf("%d %d %d %d\n",x.fi,x.se,S[i][res].fi,S[i][res].se);
//    }
    S[i][res] = x;
//    DEBUG(res);
    return res;
}

struct Node{
    int i,j,k;
    Node(int i=0,int j=0,int k=0) : i(i),j(j),k(k) {}
    inline int& f(){
//        if(!::f[i].count(calc(MP(j,k)))) ::f[i][calc(MP(j,k))] = -INF;
        return ::f[i][calc(i,MP(j,k))];
    }

    inline P& pre(){
//        if(!::pre[i].count(calc(MP(j,k)))) ::pre[i][calc(MP(j,k))] = MP(-1,-1);
        return ::pre[i][calc(i,MP(j,k))];
    }

    inline int& tp(){
//        if(!::tp[i].count(calc(MP(j,k)))) ::tp[i][calc(MP(j,k))] = -1;
        return ::tp[i][calc(i,MP(j,k))];
    }
};

std::queue<Node> q;

inline void update(Node s,Node t,int v,int type){
//    bool flag = !f[t.i].count(MP(t.j,t.k));
    if(t.f() < v){
  //      if(flag) q.push(t);
        if(!vis[t.i][calc(t.i,MP(t.j,t.k))]) q.push(t),vis[t.i][calc(t.i,MP(t.j,t.k))] = 1;
        t.f() = v;
        t.pre() = MP(s.j,s.k);
        t.tp() = type;
    }
}

std::vector<int> p0,pO;
int cnt[MAXN],ts;

inline void bfs(){
    FOR(i,0,X) f[1][calc(1,MP(i,X-i))] = 0,q.push(Node(1,i,X-i));
    while(!q.empty()){
        Node v = q.front();q.pop();
        int i = v.i,j = v.j,k = v.k;
        if(i == n+1) continue;
        update(v,Node(i+1,std::max(0,j-a[i]),k),v.f()+b[i]-std::max(0,j-a[i]),0);
        update(v,Node(i+1,j,std::max(0,k-a[i])),v.f(),1);
    }
    int ans = -INF;Node ps;
    FOR(x,0,MAXN*2-1){
        P xx = S[n+1][x];
        int j = xx.fi,k = xx.se;
        if(!k && f[n+1][x] > ans){
            ans = f[n+1][x];ps = Node(n+1,xx.fi,xx.se);
        }
    }
    while(ps.i > 1 && ps.j != -1 && ps.k != -1){
        if(ps.tp()) p0.pb(ps.i-1);
        else pO.pb(ps.i-1);
        P t = ps.pre();
        ps = Node(ps.i-1,t.fi,t.se);
    }
    std::reverse(all(pO));
    printf("%d\n",ans);
    for(auto x:p0) printf("%d ",_[x-1].se);
    for(auto x:pO) printf("%d ",_[x-1].se);
    puts("");exit(0);
}

int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    scanf("%d%d",&X,&n);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n) scanf("%d",b+i);
    FOR(i,1,n) _.pb(MP(MP(a[i],b[i]),i));
    std::sort(all(_));std::reverse(all(_));
    CLR(f,-0x3f);
//    DEBUG(_[0].se);
    FOR(i,1,n) a[i] = _[i-1].fi.fi,b[i] = _[i-1].fi.se;
    bfs();
    return 0;
}
