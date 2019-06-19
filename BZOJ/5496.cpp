#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;
const int MAXM = 4200000+5;
char str[MAXN];
int N,sa[MAXN],tax[MAXN],M;
int height[MAXN],pool1[MAXN],*rk = pool1,pool2[MAXN],*tp = pool2;
 
inline void sort(){
    FOR(i,0,M) tax[i] = 0;
    FOR(i,1,N) tax[rk[i]]++;
    FOR(i,1,M) tax[i] += tax[i-1];
    ROF(i,N,1) sa[tax[rk[tp[i]]]--] = tp[i];
}
void calheight();
inline void SuffixSort(){
    M = 75;
    FOR(i,1,N) rk[i] = str[i]-'0'+1,tp[i] = i;
    sort();
    for(int w = 1,p = 0;p < N;w <<= 1,M = p){
        p = 0;
        FOR(i,1,w) tp[++p] = N-w+i;
        FOR(i,1,N) if(sa[i] > w) tp[++p] = sa[i]-w;
        sort();
        std::swap(tp,rk);
        rk[sa[1]] = p = 1;
        FOR(i,2,N) rk[sa[i]] = (tp[sa[i-1]] == tp[sa[i]] && tp[sa[i-1]+w] == tp[sa[i]+w]) ? p : ++p;
    }
    calheight();
}
 
inline void calheight(){
    int j,k = 0;
    FOR(i,1,N){
        if(k) --k;
        j = sa[rk[i]-1];
        while(str[i+k] == str[j+k]) k++;
        height[rk[i]] = k;
    }
}

int st[40][MAXN];

inline void init(){
    FOR(i,2,N) st[0][i] = height[i];
    int log2n = log2(N);
    FOR(i,1,log2n){
        FOR(j,1,(1<<i)) st[i][j] = 0;
        for(int j = (1<<i)|1;j <= N;++j){
            st[i][j] = std::min(st[i-1][j],st[i-1][j-(1<<(i-1))]);
        }
    }
}

int NA,la[MAXN],ra[MAXN];
int NB,lb[MAXN],rb[MAXN];

std::vector<int> G[MAXM];
int ru[MAXM];

inline void add(int u,int v){
    //printf("%d %d\n",u,v);
    G[u].pb(v);++ru[v];
}

int cnt,root[MAXN],lc[MAXM],rc[MAXM],val[MAXM];

inline void modify(int &rt,int l,int r,int p,int x){
    lc[++cnt] = lc[rt];rc[cnt] = rc[rt];
    if(rt) add(cnt,rt);
    val[rt = cnt] = 0;
    if(l == r){add(rt,x);return;}
    int mid = (l + r) >> 1;
    if(p <= mid) modify(lc[rt],l,mid,p,x),add(rt,lc[rt]);
    else modify(rc[rt],mid+1,r,p,x),add(rt,rc[rt]);
}

inline void link(int rt,int l,int r,int L,int R,int x){
    if(!rt || r < L || l > R) return;
    if(L <= l && r <= R){
        add(x,rt);return;
    }
    int mid = (l + r) >> 1;
    link(lc[rt],l,mid,L,R,x);
    link(rc[rt],mid+1,r,L,R,x);
}

struct sub{
    int l,len,type,id;
    sub(int l=0,int len=0,int type=0,int id=0) : l(l), len(len), type(type), id(id) {}
    
    friend bool operator < (const sub &a,const sub &b){
        return a.len == b.len ? a.type < b.type : a.len > b.len;
    }
}s[MAXN<<1];

LL dis[MAXM];

inline void Solve(){
    scanf("%s",str+1);N = strlen(str+1);
    SuffixSort();
    init();
    scanf("%d",&NA);
    FOR(i,1,NA){
        scanf("%d%d",la+i,ra+i);
        s[i] = sub(rk[la[i]],ra[i]-la[i]+1,1,i);
    }
    scanf("%d",&NB);
    FOR(i,1,NB){
        scanf("%d%d",lb+i,rb+i);
        s[NA+i] = sub(rk[lb[i]],rb[i]-lb[i]+1,2,i);
    }
    std::sort(s+1,s+NA+NB+1);cnt = NA+NB;
    FOR(i,1,NA) val[i] = ra[i]-la[i]+1;
    FOR(i,1,NB) val[NA+i] = 0;
    int tot = 0;
    FOR(i,1,NA+NB){
        sub p = s[i];
        if(p.type & 1) ++tot,modify(root[tot] = root[tot-1],1,N,p.l,p.id);
        else{
            int L = p.l,R = p.l;
            int t = log2(p.l-1);
            ROF(j,t,0) if(st[j][L] >= p.len) L -= 1<<j;
            t = log2(N-p.l);
            ROF(j,t,0) if(R+(1<<j) <= N && st[j][R+(1<<j)] >= p.len) R += 1<<j;
            link(root[tot],1,N,L,R,NA+p.id);
        }
    }
    int m;scanf("%d",&m);
    while(m--){
        int x,y;scanf("%d%d",&x,&y);
        add(x,NA+y);
    }
    LL ans = 0;tot = 0;
    std::queue<int> q;
    FOR(i,1,cnt){
        dis[i] = val[i];
        if(!ru[i]) q.push(i),++tot;
    }
    while(!q.empty()){
        int v = q.front();q.pop();
        ans = std::max(ans,dis[v]);
        for(auto to:G[v]){
            dis[to] = std::max(dis[to],dis[v]+val[to]);
            if(!--ru[to]) q.push(to),++tot;
        }
    }
    printf("%lld\n",cnt != tot ? -1ll : ans);
    FOR(i,1,cnt) ru[i] = 0,G[i].clear();
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
