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

const int MAXN = 2e5 + 5;
int f[MAXN],ch[MAXN][2],sz[MAXN],val[MAXN];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){sz[x] = sz[lc]+sz[rc]+val[x];}
inline bool nroot(int x){return ch[f[x]][0]==x||ch[f[x]][1]==x;}
inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);
}
inline void splay(int x){
    while(nroot(x)){
        int y = f[x],z = f[y];
        if(nroot(y)) rotate((ch[z][1]==y)^(ch[y][1]==x)?x:y);
        rotate(x);
    }
}
inline int access(int x){
    int y = 0;for(;x;x=f[y=x]){
        splay(x);rc=y;pushup(x);
    }
    return y;
}
inline int dis(int x,int y){
    access(x);splay(x);int dx=sz[x];int l=access(y);splay(y);int dy=sz[y];access(l);splay(l);
    return dx+dy-2*sz[l];
}
inline void link(int x,int y){access(x);splay(x);f[x]=y;}
inline void cut(int x){access(x);splay(x);lc=f[lc]=0;pushup(x);}
int n,m,N;
int xd[MAXN],now,sd[MAXN],tp;
int L[MAXN],R[MAXN];

struct Node{
    int opt,u,v,id;
    Node(int opt=0,int u=0,int v=0,int id=0) : opt(opt),u(u),v(v),id(id) {}
    bool operator < (const Node &t) const {
        return opt > t.opt;
    }
};
std::vector<Node> G[MAXN];
int ans[MAXN];
int main(){
    scanf("%d%d",&n,&m);
    sd[tp = 1] = N = 1;L[1] = 1;R[1] = n;val[1] = sz[1] = 1;
    int now = ++N;link(2,1);CLR(ans,-1);
    FOR(i,1,m){
        int opt;scanf("%d",&opt);
        if(opt == 0){
            int l,r;scanf("%d%d",&l,&r);
            sd[++tp] = ++N;L[tp] = l;R[tp] = r;val[N] = sz[N] = 1;link(N,now);
        }
        if(opt == 1){
            int l,r,x;scanf("%d%d%d",&l,&r,&x);
            l = std::max(l,L[x]);r = std::min(r,R[x]);
            if(l > r) continue;++N;
            link(N,now);
            G[l].pb(Node(1,N,sd[x]));G[r+1].pb(Node(1,N,now));
            now = N;
        }
        if(opt == 2){
            int x,u,v;scanf("%d%d%d",&x,&u,&v);
            G[x].pb(Node(0,sd[u],sd[v],i));
        }
    }
    FOR(i,1,n) std::sort(all(G[i]));
    FOR(i,1,n){
        for(auto x:G[i]){
            if(x.opt){
                cut(x.u);link(x.u,x.v);
            }
            else{
                ans[x.id] = dis(x.u,x.v);
            }
        }
    }
    FOR(i,1,m) if(ans[i] != -1) printf("%d\n",ans[i]);
    return 0;
}
/*
 * 一开始把整个在1位置的树建出来
 * 对于某个树的1操作相当于是把这个操作后面的点都移动到另一个子树上
 * 剩下的对时间就没限制了
 */
