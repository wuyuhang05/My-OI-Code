/*
 * Author: RainAir
 * Time: 2019-08-23 09:26:05
 */
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

const int MAXN = 1e5 + 5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)
int sm[MAXN],n,cs;

inline void pushup(int x){
    sm[x] = sm[lc] + sm[rc];
}

inline void update(int x,int l,int r,int ps,int d){
    if(l == r){
        sm[x] += d;return;
    }
    int mid = (l + r) >> 1;
    if(ps <= mid) update(lc,l,mid,ps,d);
    else update(rc,mid+1,r,ps,d);
    pushup(x);
}

inline void del(int x,int l,int r){
    if(l == r){
        sm[x]--;return;
    }
    int mid = (l + r) >> 1,ls = sm[lc];
    ls ? del(lc,l,mid) : del(rc,mid+1,r);
    pushup(x);
}

inline int query(int x,int l,int r,int rk){
    if(l == r) return l;
    int mid = (l + r) >> 1,ls = sm[lc];
    return rk <= ls ? query(lc,l,mid,rk) : query(rc,mid+1,r,rk-ls);
}

int a[MAXN],b[MAXN];
int opt[MAXN];char str[233];
int cnt;
std::queue<int> q;

inline void clear(){
    CLR(a,0);CLR(b,0);cnt = 0;CLR(sm,0);CLR(opt,0);
}

inline void Solve(){
    FOR(i,1,n){
        scanf("%s",str);
        opt[i] = (str[0] == 'i' ? 1 : (str[0] == 'o' ? 2 : 3));
        if(opt[i] == 1) scanf("%d",a+i),b[++cnt] = a[i];
    }
    std::sort(b+1,b+cnt+1);
    FOR(i,1,n) a[i] = std::lower_bound(b+1,b+cnt+1,a[i]) - b;
    int sz = 0;
    FOR(i,1,n){
        if(opt[i] == 1) update(1,1,n,a[i],1),sz++,q.push(a[i]);
        if(opt[i] == 2) update(1,1,n,q.front(),-1),sz--,q.pop();
        if(opt[i] == 3) printf("%d\n",b[query(1,1,n,(sz/2)+1)]);
    }
    while(!q.empty()) q.pop();
    clear();
}

int main(){
    while(~scanf("%d",&n)){
        printf("Case #%d:\n",++cs);Solve();
    }
    return 0;
}
