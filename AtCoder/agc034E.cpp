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

const int MAXN = 2000+5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int n;
char S[MAXN];
int sm[MAXN],num[MAXN],mx[MAXN];
int f[MAXN];

inline void dfs1(int v,int fa=0){
    num[v] = S[v]=='1';mx[v] = 0;sm[v] = 0;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs1(e[i].to,v);
        sm[v] += sm[e[i].to]+num[e[i].to];
        num[v] += num[e[i].to];
        if(sm[mx[v]]+num[mx[v]] < sm[e[i].to]+num[e[i].to]) mx[v] = e[i].to;
    }
}

inline void dfs2(int v,int fa=0){
    f[v] = 0;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs2(e[i].to,v);
    }
    int mx = sm[::mx[v]]+num[::mx[v]];
    if(2*mx <= sm[v]) f[v] = sm[v]/2;
    else{
        int k = std::max(0,std::min(f[::mx[v]],(2*mx-sm[v])/2));
        f[v] = sm[v]-mx+k;
    }
}
/*
 * if 2*mx <= sm then f[v]=sm/2
 * else f[v]=sm-mx+k
 * 0 <= k <= f[u],k <= (2*mx-sm)/2
 */
int ans = 1e9;
inline void work(int rt){
    dfs1(rt);dfs2(rt);
    if(f[rt] == sm[rt]/2 && !(sm[rt]&1)) ans = std::min(ans,sm[rt]/2);
}

int main(){
    scanf("%d%s",&n,S+1);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    work(2);
    FOR(i,1,n) work(i);
    printf("%d\n",ans==1e9 ? -1 : ans);
    return 0;
}
