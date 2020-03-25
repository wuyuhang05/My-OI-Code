#include<bits/stdc++.h>

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

const int MAXN = 1e5 + 5;
int n,m,A,B,C;

int N;
struct Edge{
    int x,y,p,opt,id;
    Edge(int x=0,int y=0,int p=0,int opt=0,int id=0) : x(x),y(y),p(p),opt(opt),id(id) {}

    bool operator  < (const Edge &t) const {
        return p == t.p ? opt < t.opt : p < t.p;
    }
}a[MAXN<<2];

std::deque<int> G[MAXN];
LL f[MAXN<<1];
int p[MAXN<<1],q[MAXN<<1];
#define X(i) (q[i])
#define Y(i) (1ll*f[i]+1ll*A*q[i]*q[i]-1ll*B*q[i])

inline LL calc(LL x){
    return A*x*x+B*x+C;
}

inline void insert(std::deque<int>& G,int x){
    if(f[x] == 1e18) return;
    int sz = G.size();
    while(sz >= 2 && 1ll*(X(G[sz-1])-X(G[sz-2]))*(Y(x)-Y(G[sz-1])) < 1ll*(X(x)-X(G[sz-1]))*(Y(G[sz-1])-Y(G[sz-2]))) G.pop_back(),sz--;
    G.pb(x);
}

inline double kkk(int x,int y){
    return 1.0*(Y(x)-Y(y))/(X(x)-X(y));
}

inline void qry(std::deque<int>& G,int x){
    while(G.size() >= 2 && 1ll*(Y(G[0])-Y(G[1])) >= 2ll*(X(G[0])-X(G[1]))*A*p[x]) G.pop_front();
    f[x] = f[G[0]]+calc(p[x]-q[G[0]]);
//    f[x] = Y(G[0])-2*A*p[x]*q[G[0]]+B*p[x]+C+A*p[x]*p[x];
}
std::vector<int> tmp;
signed main(){
    scanf("%d%d%d%d%d",&n,&m,&A,&B,&C);
    FOR(i,1,m){
        int x,y,p,q;scanf("%d%d%d%d",&x,&y,&p,&q);::p[i] = p;::q[i] = q;
        a[++N] = Edge(x,y,p,1,i);a[++N] = Edge(x,y,q,-1,i);
        if(y == n) tmp.pb(i);
    }
    std::sort(a+1,a+N+1);
    FOR(i,1,N){
        if(a[i].opt == 1){ // 查询
            if(G[a[i].x].empty()) f[a[i].id] = a[i].x==1?calc(a[i].p):1e18;
            else qry(G[a[i].x],a[i].id);
        }
        else{ // 修改
            insert(G[a[i].y],a[i].id);
        }
    }
    LL ans = 1e18;
    for(auto x:tmp) ans = std::min(ans,f[x]+q[x]);
    printf("%lld\n",ans);
    return 0;
}
/*
 * 暴力：

f[i]表示走完第i条边的最小代价

$f[i] = f[j]+cost(p_i-q_j)$

要求 $y_j = x_i,q_j \leq p_i$

考虑扫描线 遇到左端点就查询 遇到右端点就加入

现在只有要求 $y_j=x_i$ 了

$f[i] = f[j]+cost(p_i-q_j)$

$f[i]-Bp_i-C-Ap_i^2 = (f[j]+Aq_j^2-Bq_j)-2Ap_iq_j$

令 $F[i] = f[i]+Aq_j^2-Bq_j$

$f’[i] = F[j]-2Ap_iq_j$

考虑当 $j<k$ 且从k转移更优的时刻：

$\frac{F[j]-F[k]}{q_j-q_k} \leq 2Ap_i$

还是对于每个 $k=y_j$ 都搞出来一个凸包 维护一下就好了
*/
