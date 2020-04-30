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
int ch[MAXN][2],f[MAXN];
int sz[MAXN],col[MAXN],ls[MAXN],rs[MAXN];
std::multiset<int> S[MAXN];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline bool nroot(int x){return ch[f[x]][0]==x||ch[f[x]][1]==x;}
inline int top(int x){return S[x].empty() ? 1e9 : *S[x].begin();}

inline void pushup(int x){//分是否经过这个点讨论
    sz[x] = sz[lc]+sz[rc]+1;
    ls[x] = std::min(ls[lc],sz[lc]+std::min(col[x]?1000000000:0,std::min(top(x),ls[rc])+1));
    rs[x] = std::min(rs[rc],sz[rc]+std::min(col[x]?1000000000:0,std::min(top(x),rs[lc])+1));
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);
}
int st[MAXN];
inline void splay(int x){
    while(nroot(x)){
        int y = f[x],z = f[y];
        if(nroot(y)) rotate((ch[z][1]==y)^(ch[y][1]==x) ? x : y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x){
    for(int y = 0;x;x = f[y = x]){
        splay(x);
        S[x].insert(ls[rc]);
        if(S[x].count(ls[y])) S[x].erase(S[x].find(ls[y]));
        rc = y;pushup(x);
    }
}

std::vector<int> G[MAXN];

inline void dfs(int v,int fa=0){
    f[v] = fa;
    for(auto x:G[v]){
        if(x == fa) continue;
        dfs(x,v);S[v].insert(1e9);
    }
    pushup(v);
}

int main(){
    int n;scanf("%d",&n);std::fill(col,col+n+1,1);
    ls[0] = rs[0] = 1e9;
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);G[u].pb(v);G[v].pb(u);
    }
    dfs(1);int tot = 0;
    int m;scanf("%d",&m);
    while(m--){
        int opt,x;scanf("%d%d",&opt,&x);
        if(opt){
            access(x);splay(x);printf("%d\n",rs[x]>n? -1 : rs[x]);
        }
        else{
            access(x);splay(x);//Splay修改的时候一定要把点旋转上来（时间和算法正确性）
            col[x] ^= 1;
            pushup(x);
        }
    }
    return 0;
}
