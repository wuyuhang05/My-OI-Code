#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define db double
#define U unsigned
#define P std::pair<LL,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e6 + 5;
int n;LL k;
int a[MAXN];
namespace BF{
std::vector<LL> S;
    inline void Solve(){
        printf("%lld\n",k);S.pb(k);
    FOR(i,2,n){
        LL sm = 0;std::sort(all(S));
        FOR(j,1,a[i]-1) sm += S[j-1]+1;
        LL t = std::max(-1ll,k-sm);
        printf("%lld\n",t);
        if(t == -1){
            S.pb(-1);
        }
        else{
            FOR(j,1,a[i]-1) S[j-1]++;
            FOR(j,a[i],i-1) S[j-1] = 0;
            S.pb(t);
        }
    }
    exit(0);
    }
}

LL sm[MAXN];
LL tag1[MAXN],tag2[MAXN];//1=add 2=cov
int ch[MAXN][2],f[MAXN],sz[MAXN],rt,tot;
P val[MAXN];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
    sm[x] = sm[lc]+sm[rc]+val[x].fi;
    sz[x] = sz[lc]+sz[rc]+1;
}

inline void cover1(int x,LL d){
    val[x].fi += d;sm[x] += d*sz[x];tag1[x] += d;
}

inline void cover2(int x,LL d){
    val[x].fi = d;sm[x] = sz[x]*d;tag2[x] = d;tag1[x] = 0;
}

inline void pushdown(int x){
    if(tag2[x] != -233){
        if(lc) cover2(lc,tag2[x]);
        if(rc) cover2(rc,tag2[x]);
        tag2[x] = -233;
    }
    if(tag1[x]){
        if(lc) cover1(lc,tag1[x]);
        if(rc) cover1(rc,tag1[x]);
        tag1[x] = 0;
    }
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(z) ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);
}

int st[MAXN];
inline void splay(int x,int v){
    int y,z;
    st[z = 1] = y = x;
    while(f[y] != v) st[++z] = y = f[y];
    while(z) pushdown(st[z--]);
    while(f[x] != v){
        int y = f[x],z = f[y];
        if(f[y] != v) rotate((ch[z][1]==y)^(ch[y][1]==x)?x:y);
        rotate(x);
    }
    if(!v) rt = x;
    pushup(x);
}

inline int getkth(int k){
    int x = rt;
    while(233){
        pushdown(x);
        if(k <= sz[lc]) x = lc;
        else if(k == sz[lc]+1) {splay(x,0);return x;}
        else k -= sz[lc]+1,x = rc;
    }
}

inline void insert(P d){
    int v = rt,pre = 0;
    while(v) pushdown(v),v = ch[pre = v][val[v]<d];
    v = ++tot;
    if(pre) ch[pre][val[pre]<d] = v;
    ch[v][0] = ch[v][1] = 0;f[v] = pre;val[v] = d;sz[v] = 1;tag2[v] = -233;
    splay(v,0);
}

inline void insert(int d){
    int v = rt,pre = 0;
    while(v) pushdown(v),v = ch[pre = v][val[v]<val[d]];
    v = d;
    if(pre) ch[pre][val[pre]<val[d]] = v;
    f[v] = pre;
    splay(v,0);
}

int main(){
    scanf("%d%lld",&n,&k);
    FOR(i,1,n) scanf("%d",a+i);
    if(n <= 2000 ) BF::Solve();
    printf("%lld\n",k);
    insert(MP(k,1));
    FOR(i,2,n){
        if(a[i] == 1){
            printf("%lld\n",k);
            cover2(rt,0);
            insert(MP(k,i));
            continue;
        }
        int p = getkth(a[i]-1);
     //   FOR(j,1,i-1) DEBUG(val[j].fi);
        LL res = sm[p]-sm[ch[p][1]]+sz[ch[p][0]]+1;
        res = std::max(-1ll,k-res);
        printf("%lld\n",res);
        if(res == -1){
            insert(MP(-1,i));
        }
        else{
            pushdown(p);
            int v = ch[p][1];ch[p][1] = f[v] = 0;
            pushup(p);
            cover1(p,1);
            cover2(v,0);
            insert(v);
            insert(MP(res,i));
        }
    }
    return 0;
}
