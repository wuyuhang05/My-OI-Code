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

const int MAXN = 5e5 + 5;

int ch[MAXN][2],f[MAXN];
LL sm[MAXN],smi[MAXN],a[MAXN];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){sm[x] = sm[lc]+sm[rc]+smi[x]+a[x];}
inline bool nroot(int x){return ch[f[x]][0]==x||ch[f[x]][1]==x;}
inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y]=x;f[x]=z;
    ch[x][!k] = y;f[y] = x;ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);
}
inline void splay(int x){
    while(nroot(x)){
        int y = f[x],z = f[y];
        if(nroot(y)) rotate((ch[z][1]==y)^(ch[y][1]==x)?x:y);
        rotate(x);
    }
    pushup(x);
}

std::vector<int> G[MAXN];
int tp[MAXN];LL ans;
//0: 子树大 1:自己大 2: 都不大

inline void dfs(int v,int fa=0){
    LL mx = a[v];int mp = v;
    for(auto x:G[v]){
        if(x == fa) continue;
        f[x] = v;dfs(x,v);
        smi[v] += sm[x];
        if(mx < sm[x]) mx = sm[x],mp = x;
    }
    sm[v] = smi[v]+a[v];
    if((mx<<1) > sm[v]){
        ans += (sm[v]-mx)<<1;
        if(mp == v) tp[v] = 1;
        else smi[v] -= sm[mp],ch[v][1] = mp;
    }
    else tp[v] = 2,ans += sm[v]-1;
}

inline void access(int x,int w){ // add w
    for(int y = 0;x;x = f[y = x]){// 这里的y的意思就是这次加法操作是从哪个虚子树加上来的
        splay(x);
        LL S = sm[x]-sm[lc];//子树和
        if(tp[x] == 0) ans -= (S-sm[rc])<<1;//这里rc就不会有lc了 
        else if(tp[x] == 1) ans -= (S-a[x])<<1;
        else ans -= S-1;
        S += w;sm[x] += w;
        if(y) smi[x] += w;
        else a[x] += w;
        if(sm[y]<<1 > S) smi[x] += sm[rc]-sm[y],rc = y;
        if(sm[rc]<<1 > S) tp[x] = 0,ans += (S-sm[rc])<<1; // 子树过大
        else{
            if(rc) smi[x] += sm[rc],rc = 0;//实->虚
            if(a[x]<<1 > S) tp[x] = 1,ans += (S-a[x])<<1;
            else tp[x] = 2,ans += S-1;
        }
    }
}

int n,m;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);G[u].pb(v);G[v].pb(u);
    }
    dfs(1);printf("%lld\n",ans);
    FOR(i,1,m){
        int x,w;scanf("%d%d",&x,&w);
        access(x,w);printf("%lld\n",ans);
    }
    return 0;
}
