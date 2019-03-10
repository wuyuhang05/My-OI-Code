#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define nc getchar
#define Re register
#define LL long long
#define lowbit(x) (x&-x)
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline void read(int &x){
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

const int MAXN = 10000+5;
int root[MAXN],sum[MAXN<<10],lc[MAXN<<10],rc[MAXN<<10],p;
int xx[MAXN],yy[MAXN],totx,toty,n,m;
int qa[MAXN],qb[MAXN],qc[MAXN],a[MAXN];

inline void insert(int &x,int l,int r,int prev,int pos,int v){
    x = ++p;sum[x] = sum[prev]+v;lc[x] = lc[prev];rc[x] = rc[prev];
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(pos <= mid) insert(lc[x],l,mid,lc[prev],pos,v);
    else insert(rc[x],mid+1,r,rc[prev],pos,v);
}

inline int query(int l,int r,int rak){
    if(l == r) return l;
    int ls = 0,mid = (l + r) >> 1;
    FOR(i,1,totx) ls -= sum[lc[xx[i]]];
    FOR(i,1,toty) ls += sum[lc[yy[i]]];
    if(rak <= ls){
        FOR(i,1,totx) xx[i] = lc[xx[i]];
        FOR(i,1,toty) yy[i] = lc[yy[i]];
        return query(l,mid,rak);
    }
    else{
        FOR(i,1,totx) xx[i] = rc[xx[i]];
        FOR(i,1,toty) yy[i] = rc[yy[i]];
        return query(mid+1,r,rak-ls);
    }
}

int t[MAXN<<2],tot;

inline void add(int x,int v){
    int k = std::lower_bound(t+1,t+tot+1,a[x])-t;
    for(int i = x;i <= n;i += lowbit(i)) insert(root[i],1,tot,root[i],k,v);
}

int main(){
    read(n);read(m);
    FOR(i,1,n) read(a[i]),t[++tot] = a[i];
    FOR(i,1,m){
        char opt[23];
        scanf("%s",opt);
        read(qa[i]);read(qb[i]);
        if(opt[0] == 'Q') read(qc[i]);
        else t[++tot] = qb[i];
    }
    std::sort(t+1,t+tot+1);
    tot = std::unique(t+1,t+tot+1)-t-1;
    FOR(i,1,n) add(i,1);
    FOR(i,1,m){
        if(qc[i]){
            totx = toty = 0;
            for(int j = qa[i]-1;j;j -= lowbit(j)) xx[++totx] = root[j];
            for(int j = qb[i];j;j -= lowbit(j)) yy[++toty] = root[j];
            printf("%d\n",t[query(1,tot,qc[i])]);
        }
        else{
            add(qa[i],-1);a[qa[i]] = qb[i];add(qa[i],1);
        }
    }
    return 0;
}