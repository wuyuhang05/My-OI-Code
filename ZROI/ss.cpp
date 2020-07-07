//by Sshwy
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define pb push_back
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

namespace RA{
    int rnd(int p){return 1ll*rand()*rand()%p;}
    int rnd(int L,int R){return rnd(R-L+1)+L;}
}
const int N=1e5+5,M=N*2,P=1e9+7;
int n,m;

vector<int> g[N];
struct qxx{int nex,t,v;}e[M];
int h[N],le=1;
void add_path(int f,int t,int v){e[++le]={h[f],t,v},h[f]=le;}

int sz_m[N];
int ans,tot;
void dfs_m(int u,int p){
    sz_m[u]=1;
    for(int i=h[u];i;i=e[i].nex){
        int v=e[i].t;
        if(v!=p)dfs_m(v,u),sz_m[u]+=sz_m[v];
    }
    if(p){
        ans=(ans+(m-sz_m[u])*1ll*sz_m[u]%P*n%P*n%P)%P;
    }
}
int fa[N],sz[N],dep[N],big[N],id[N],top[N],totdfn;
int L[N],R[N];
void dfs1(int u,int p){ // HLD
    fa[u]=p;
    sz[u]=1,dep[u]=dep[p]+1;
    for(int v:g[u]) if(v!=p)dfs1(v,u),sz[u]+=sz[v],big[u]=(big[u] && sz[big[u]]>sz[v])?big[u]:v;
}
void dfs2(int u,int p,int tp){ // HLD
    top[u]=tp,id[u]=++totdfn;
    L[u]=id[u];
    if(big[u])dfs2(big[u],u,tp);
    for(int v:g[u])if(v!=p && v!=big[u])dfs2(v,u,v);
    R[u]=totdfn;
}
struct fenwick{
    int c[N];
    void add(int pos,int v){
        for(int i=pos;i<N;i+=i&-i)c[i]=(c[i]+v)%P;
    }
    int pre(int pos){
        int res=0;
        for(int i=pos;i>0;i-=i&-i)res=(res+c[i])%P;
        return res;
    }
};
struct seg{
    fenwick d1,d2;
    void add(int pos,int v){
        d1.add(pos,v);
        d2.add(pos,v*1ll*pos%P);
    }
    int pre(int pos){
        return (d1.pre(pos)*(pos+1ll)%P-d2.pre(pos)+P)%P;
    }
    void add(int L,int R,int v){
        add(L,v);
        add(R+1,P-v);
    }
    int qry(int L,int R){
        if(L==1)return pre(R);
        return (pre(R)-pre(L-1)+P)%P;
    }
}up,dn;
int path_up(int u){ // include self
    int res=0;
    while(u!=1){
        int v=top[u];
        if(v==1)res=(res+up.qry(id[v]+1,id[u]))%P,u=v;
        else res=(res+up.qry(id[v],id[u]))%P,u=fa[v];
    }
    return res;
}
void path_up_add(int u,int val){ // include self
    while(u!=1){
        int v=top[u];
        if(v==1)up.add(id[v]+1,id[u],val),u=v;
        else up.add(id[v],id[u],val),u=fa[v];
    }
}
int path_down(int u){ // include self
    int res=0;
    while(u!=1){
        int v=top[u];
        if(v==1)res=(res+dn.qry(id[v]+1,id[u]))%P,u=v;
        else res=(res+dn.qry(id[v],id[u]))%P,u=fa[v];
    }
    return res;
}
void path_down_add(int u,int val){ // include self
    while(u!=1){
        int v=top[u];
        if(v==1)dn.add(id[v]+1,id[u],val),u=v;
        else dn.add(id[v],id[u],val),u=fa[v];
    }
}
void node_add(int u,int v){
    long long x1=up.qry(L[1]+1,R[1]);
    long long x2=path_up(u);
    long long x3=path_down(u);
    tot=(tot+(x1-x2+x3)%P*v)%P;

    dn.add(L[1]+1,R[1],v);
    path_down_add(u,-v);
    path_up_add(u,v);
}
void dfs(int u,int p){
    for(int i=h[u];i;i=e[i].nex){
        int v=e[i].t,nd=e[i].v,s=0;
        if(v==p)s=m-sz_m[u];
        else s=sz_m[v];
        s=s*1ll*n%P;
        node_add(nd,s);
    }
    DEBUG(tot);DEBUG(u);
    ans=(ans+tot)%P;
    for(int i=h[u];i;i=e[i].nex){
        int v=e[i].t,nd=e[i].v,s=0;
        if(v==p)s=m-sz_m[u];
        else s=sz_m[v];
        s=s*1ll*n%P;
        node_add(nd,(P-s)%P);
    }
    for(int i=h[u];i;i=e[i].nex){
        int v=e[i].t;
        if(v!=p)dfs(v,u);
    }
}
signed main(){
//    freopen("C.in","r",stdin);
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n-1){
        int u,v;
        scanf("%lld%lld",&u,&v);
        g[u].pb(v);
        g[v].pb(u);
    }
    FOR(i,1,m-1){
        int a,b,u,v;
        scanf("%lld%lld%lld%lld",&a,&b,&u,&v);
        add_path(a,b,u);
        add_path(b,a,v);
    }
    dfs_m(1,0);
    dfs1(1,0);
    dfs2(1,0,1);
    FOR(i,1,n){
        up.add(id[i],id[i],sz[i]); // subtree's goes up
        dn.add(id[i],id[i],n-sz[i]); // goes down
    }
    FOR(u,1,n)if(fa[u]){
        tot=(tot+sz[u]*1ll*(n-sz[u]))%P; // up(id[u]) * down(id[u]);
    }
    (ans += 1ll*tot*n%P)%=P;
    tot = 0;
    DEBUG(ans);
    dfs(1,0);
    ans=(ans+P)%P;
    printf("%lld\n",ans);
    return 0;
}
