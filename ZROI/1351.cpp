#pragma GCC optimize("Ofast")
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


const int MAXN = 2e5 + 5;
int f[MAXN],ch[MAXN][2],sz[MAXN],val[MAXN];LL tag[MAXN],sm[MAXN];
int ID[MAXN];
std::vector<P> TT;
int S[MAXN];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
    sz[x] = sz[lc]+sz[rc]+1;
}

inline void pushdown(int x){
    if(tag[x]){
        if(lc) tag[lc] += tag[x],sm[lc] += tag[x];
        if(rc) tag[rc] += tag[x],sm[rc] += tag[x];
        tag[x] = 0;
    }
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;f[w] = y;
    pushup(y);pushup(x);
}

int root[MAXN];

inline void splay(int id,int x,int v){
    int y,z;
    while((y = f[x]) != v){
        if((z = f[y]) != v) rotate((ch[z][1]==y)^(ch[y][1]==x)?x:y);
        rotate(x);
    }
    if(!v) root[id] = x;
}

inline int getkth(int id,int rk){
    int x = root[id];
    while(233){
        pushdown(x);
        if(rk <= sz[lc]) x = lc;
        else if(rk == sz[lc]+1){
            splay(id,x,0);
            return x;
        }
        else rk -= sz[lc]+1,x = rc;
    }
}
int tot = 0;
inline void insert(int id,int ver){
    int v = root[id],pre = 0;
    while(val[v] != val[ver] && v) pushdown(v),v = ch[pre = v][val[v]<val[ver]];
    //assert(v == 0);assert(tag[pre] == 0);
    sz[ver] = 1;if(pre) ch[pre][val[pre]<val[ver]] = ver;
    f[ver] = pre;ch[ver][0] = ch[ver][1] = 0;
    splay(id,ver,0);
}

std::vector<int> node;

inline void dfs(int x){
    pushdown(x);
    if(lc) dfs(lc);
    node.pb(x);
    if(rc) dfs(rc);
}

struct Edge{
    int to,nxt;
}e[MAXN];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}
int a[MAXN];

inline void merge(int x,int y){
    if(sz[root[x]] < sz[root[y]]) std::swap(root[x],root[y]);
    node.clear();dfs(root[y]);
    for(auto v:node) insert(x,v);
}
LL cf[MAXN];
int dfn[MAXN],nfd[MAXN];

inline void modify(int l,int r,LL d){
    if(l > r) return;
    cf[l] += d;cf[r+1] -= d;
}
int n;

inline void debug(int x){
    if(lc) debug(lc);
    printf("%d ",ID[x]);
    if(rc) debug(rc);
}

inline void Dfs(int v){
    static int ts = 0;dfn[v] = ++ts;
    val[++tot] = a[v];sm[tot] = 0;ID[tot] = v;
    insert(v,tot);
    for(int i = head[v];i;i = e[i].nxt){
        Dfs(e[i].to);
        merge(v,e[i].to);
    }
    if(sz[root[v]] == 1){
        tag[root[v]] += 1e5;sm[root[v]] += 1e5;
        modify(1,dfn[v]-1,S[val[root[v]]]);
        modify(dfn[v]+1,n,S[val[root[v]]]);
//        if(v == 2) dfs(root[v]),DEBUG(sm[root[v]]),DEBUG(tag[root[v]]);
        return;
    }
    // [dfn[v],dfn[v]+sz[v]-1]
    getkth(v,(sz[root[v]]+1)/2);
    int now = root[v],suf = ch[now][1];
    modify(1,dfn[v]-1,S[val[now]]);
    modify(dfn[v]+sz[root[v]],n,S[val[now]]);
    while(ch[suf][0]) pushdown(suf),suf = ch[suf][0];
    pushdown(v);
    tag[now] += S[val[suf]];sm[now] += S[val[suf]];
    pushdown(ch[now][1]);
    tag[ch[now][1]] += S[val[now]]-S[val[suf]];
    sm[ch[now][1]] += S[val[now]]-S[val[suf]];
}
LL ans[MAXN];
int main(){
    //freopen("A.in","r",stdin);
    //freopen("ex_A2.in","r",stdin);
    //freopen("a.out","w",stdout);
    read(n);
    FOR(i,1,n) read(a[i]),TT.pb(MP(a[i],i));
    std::sort(all(TT));
    FOR(i,0,(int)TT.size()-1) a[TT[i].se] = i+1,S[i+1] = TT[i].fi;
    FOR(i,2,n){
        int p;read(p);
        add(p,i);
    }
    Dfs(1);
    node.clear();dfs(root[1]);
    for(auto x:node) ans[ID[x]] = sm[x];
    FOR(i,1,n) cf[i] += cf[i-1];
//    DEBUG(cf[dfn[2]]);DEBUG(sm[dfn[2]]);
    FOR(i,1,n) printf("%lld\n",ans[i]+cf[dfn[i]]);
    return 0;
}

