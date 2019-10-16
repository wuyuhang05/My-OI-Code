/*
 * Author: RainAir
 * Time: 2019-10-03 20:19:30
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;

int mn[(MAXN<<5)+3],lc[(MAXN<<5)+3],rc[(MAXN<<5)+3],root[MAXN],tot;

inline void insert(int prev,int &v,int l,int r,int p,int d){
    mn[v = ++tot] = mn[prev],lc[v] = lc[prev],rc[v] = rc[prev];
    if(l == r){
        mn[v] = d;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) insert(lc[prev],lc[v],l,mid,p,d);
    else insert(rc[prev],rc[v],mid+1,r,p,d);
    mn[v] = std::min(mn[lc[v]],mn[rc[v]]);
}

inline int query(int v,int l,int r,int d){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(mn[lc[v]] < d) return query(lc[v],l,mid,d);
    else return query(rc[v],mid+1,r,d);
}

int a[MAXN],pre[MAXN],n,m;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i),a[i] = std::min(a[i],n+1);
    FOR(i,1,n) insert(root[i-1],root[i],0,n+1,a[i],i);
    FOR(i,1,m){
        int l,r;scanf("%d%d",&l,&r);
        printf("%d\n",query(root[r],0,n+1,l));
    }
    return 0;
}
