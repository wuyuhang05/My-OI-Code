#include <bits/stdc++.h>

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

const int MAXN = 300000+5;
char str[MAXN];
int n,a[MAXN];
LL f[MAXN],mx[MAXN],sz[MAXN],ans[MAXN],mn[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

struct SA{
    int sa[MAXN],rk[MAXN],tp[MAXN],tax[MAXN];
    int H[MAXN];
    int M;

    inline void sort(){
        FOR(i,0,M) tax[i] = 0;
        FOR(i,1,n) tax[rk[i]]++;
        FOR(i,1,M) tax[i] += tax[i-1];
        ROF(i,n,1) sa[tax[rk[tp[i]]]--] = tp[i];
    }

    inline void build(){
        M = 26;
        FOR(i,1,n) rk[i] = str[i]-'a'+1,tp[i] = i;
        sort();
        for(int w=1,p=0;p < n;w <<= 1,M = p){
            p = 0;
            FOR(i,1,w) tp[++p] = n-w+i;
            FOR(i,1,n) if(sa[i] > w) tp[++p] = sa[i]-w;
            sort();std::swap(rk,tp);
            rk[sa[p = 1]] = 1;
            FOR(i,2,n) rk[sa[i]] = (tp[sa[i]] == tp[sa[i-1]] && tp[sa[i]+w] == tp[sa[i-1]+w]) ? p : ++p;
        }
        int j = 0;
        FOR(i,1,n){
            if(j) --j;
            while(str[i+j] == str[sa[rk[i]-1]+j]) ++j;
            H[rk[i]] = j;
        }
    }
}sa;

std::vector<int> G[MAXN];
LL sm = 0,res = 0;

inline void merge(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return;
    if(sz[fx] < sz[fy]) std::swap(fx,fy);
    sm += sz[fx]*sz[fy];
    f[fy] = fx;sz[fx] += sz[fy];
    LL t = std::max(std::max(mx[fx]*mx[fy],mn[fx]*mn[fy]),std::max(mx[fx]*mn[fy],mn[fx]*mx[fy]));
    ans[fx] = std::max(ans[fx],std::max(ans[fy],t));
    res = std::max(res,ans[fx]);
    mx[fx] = std::max(mx[fx],mx[fy]);
    mn[fx] = std::min(mn[fx],mn[fy]);
}

LL _[MAXN],__[MAXN];

int main(){
    scanf("%d",&n);
    std::iota(f+1,f+n+1,1);std::fill(sz+1,sz+n+1,1);
    scanf("%s",str+1);res = -1e18;
    FOR(i,1,n) scanf("%lld",mx+i),mn[i] = mx[i],ans[i] = -1e18;
    sa.build();
    FOR(i,1,n) G[sa.H[i]].pb(i);
    ROF(i,n-1,0){
        for(auto x:G[i]){
            if(sa.sa[x-1]) merge(sa.sa[x-1],sa.sa[x]);
//            printf("%d %d %d\n",i,sa.sa[x-1],sa.sa[x]);
        }
        _[i] = sm;__[i] = res;
    }
//    DEBUG(mx[find(1)]);DEBUG(mn[find(1)]);
    FOR(i,0,n-1) printf("%lld %lld\n",_[i],!_[i] ? 0 : __[i]);
    return 0;
}
