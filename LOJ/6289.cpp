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

const int ha = 998244353;
const int G = 3;
const int Gn = 332748118;
const int MAXN = 1e6 + 5;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

namespace Polynomial{
    struct Poly{
        std::vector<int> x;
        int deg(){return (int)x.size()-1;}
        inline void ext(int n){x.resize(n+1);}
        int& operator [] (const int &n){
            return x[n];
        }
    };
    
    int r[MAXN],N,len;

    inline void init(int n){
        N = 1,len = 0;while(N <= n) N <<= 1,len++;
        FOR(i,0,N) r[i] = r[i>>1]>>1|((i&1)<<(len-1));
    }

    inline void NTT(Poly &A,int opt){
        A.ext(N);
        FOR(i,0,N-1) if(i < r[i]) std::swap(A[i],A[r[i]]);
        for(int mid = 1;mid < N;mid <<= 1){
            int W = qpow(opt==-1?Gn:G,(ha-1)/(mid<<1));
            for(int j = 0;j < N;j += (mid<<1)){
                for(int k = 0,w = 1;k < mid;++k,w = 1ll*w*W%ha){
                    int x = A[j+k],y = 1ll*w*A[j+mid+k]%ha;
                    A[j+k] = (x+y)%ha;A[j+mid+k] = (x+ha-y)%ha;
                }
            }
        }
        if(opt == -1){
            int inv = qpow(N);
            FOR(i,0,N-1) A[i] = 1ll*A[i]*inv%ha;
        }
    }

    Poly operator * (Poly A,Poly B){
        int len = A.deg()+B.deg();init(len);
        NTT(A,1);NTT(B,1);
        FOR(i,0,N-1) A[i] = 1ll*A[i]*B[i]%ha;
        NTT(A,-1);
        A.ext(len);
        return A;
    }

    Poly operator + (Poly A,Poly B){
        if(A.deg() < B.deg()) std::swap(A,B);
        FOR(i,0,B.deg()) (A[i] += B[i]) %= ha;
        return A;
    }

    Poly operator - (Poly A,Poly B){
        if(A.deg() < B.deg()) std::swap(A,B);
        FOR(i,0,B.deg()) (A[i] += ha-B[i]) %= ha;
        return A;
    }
}
using namespace Polynomial;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int tp[MAXN],son[MAXN],sz[MAXN],fa[MAXN];

inline void dfs1(int v){
    sz[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa[v]) continue;
        fa[e[i].to] = v;
        dfs1(e[i].to);
        sz[v] += sz[e[i].to];
        if(sz[son[v]] < sz[e[i].to]) son[v] = e[i].to;
    }
}

inline void dfs2(int v,int tp){
    ::tp[v] = tp;
    if(son[v]) dfs2(son[v],tp);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa[v] || e[i].to == son[v]) continue;
        dfs2(e[i].to,e[i].to);
    }
}

struct Node{
    Poly f[2][2];// 左右是否选
};
Poly g[MAXN][2];// 是否选自己

Node operator + (Node A,Node B){
    Node ans;
    ans.f[1][1] = A.f[1][0]*(B.f[0][1]+B.f[1][1])+A.f[1][1]*B.f[0][1];
    ans.f[1][0] = A.f[1][0]*(B.f[0][0]+B.f[1][0])+A.f[1][1]*B.f[0][0];
    ans.f[0][1] = A.f[0][0]*(B.f[0][1]+B.f[1][1])+A.f[0][1]*B.f[0][1];
    ans.f[0][0] = A.f[0][0]*(B.f[1][0]+B.f[0][0])+A.f[0][1]*B.f[0][0];
    return ans;
}

Node work(std::vector<int> &chain,int l,int r){ // 重链合并
    if(l == r){
        Node res;
        res.f[0][0] = g[chain[l]][0];
        res.f[0][1].x.pb(0);res.f[1][0].x.pb(0);
        res.f[1][1] = g[chain[l]][1];
        return res;
    }
    int mid = (l+r)>>1;
    return work(chain,l,mid)+work(chain,mid+1,r);
}

// 轻链合并
struct NODE{
    Poly f[2];
};

NODE operator + (NODE A,NODE B){
    A.f[0] = A.f[0]*B.f[0];
    A.f[1] = A.f[1]*B.f[1];
    return A;
}

NODE work2(std::vector<int> &chain,int l,int r){
    if(l > r){
        NODE res;
        res.f[0].x.pb(1);res.f[1].x.pb(1);
        return res;
    }
    if(l == r){
        NODE res;
        res.f[0] = g[chain[l]][0]+g[chain[l]][1];
        res.f[1] = g[chain[l]][0];
        return res;
    }
    int mid = (l+r)>>1;
    return work2(chain,l,mid)+work2(chain,mid+1,r);
}

void get2(int);
void get1(int);
int w[MAXN];
inline void get2(int v){
    g[v][0].x.pb(1);
    g[v][1].x.pb(0);
    g[v][1].x.pb(w[v]);
    std::vector<int> chain;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa[v] || e[i].to == son[v]) continue;
        get1(e[i].to);chain.pb(e[i].to);
    }
    NODE ans = work2(chain,0,(int)chain.size()-1);
    g[v][0] = g[v][0]*ans.f[0];
    g[v][1] = g[v][1]*ans.f[1];
}

inline void get1(int v){
    std::vector<int> chain;
    int now = v;
    while(now){
        chain.pb(now);now = son[now];
    }
    FOR(i,0,(int)chain.size()-1) get2(chain[i]);
    Node res = work(chain,0,(int)chain.size()-1);
    g[v][0] = res.f[0][0]+res.f[0][1];
    g[v][1] = res.f[1][0]+res.f[1][1];
}

int n,m;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",w+i);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    dfs1(1);dfs2(1,1);
    get1(1);
    if(m > g[1][0].deg() && m > g[1][1].deg()) puts("0");
    else printf("%d\n",(g[1][0]+g[1][1])[m]);
    return 0;
}
/*
 * f[i][0/1] i点 第i个点是否选 i次项系数表示选了i个的答案
 * f[i][0] = \sum (f[j][0]+f[j][1])
 * f[i][1] = w[i]\sum f[j][0]
 * 链分治 先对于所有轻儿子暴力算出多项式 然后在重链上设 g[0/1][0/1] 表示左端点/右端点是否选 分治合并
 */
