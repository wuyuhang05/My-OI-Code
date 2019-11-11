/*
 * Time: 2019-11-11 21:43:30
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

const int MAXN = 3e6 + 5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)
int sm[MAXN<<2];

inline void build(int x,int l,int r){
    sm[x] = r-l+1;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
}

inline void update(int x,int l,int r,int rk){
    sm[x]--;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(rk <= sm[lc]) update(lc,l,mid,rk);
    else update(rc,mid+1,r,rk-sm[lc]);
}

inline int query(int x,int l,int r,int rk){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(rk <= sm[lc]) return query(lc,l,mid,rk);
    return query(rc,mid+1,r,rk-sm[lc]);
}

int k,n;
int l[MAXN],r[MAXN];
char str[MAXN];
int fa[MAXN];
char ans[MAXN];

int main(){
    scanf("%s",str+1);
    scanf("%d%d",&k,&n);
    FOR(i,1,n) scanf("%d%d",l+i,r+i);
    build(1,1,k);
    ROF(i,n,1){
        if(r[i] < sm[1]){
            int now = l[i]+1;
            if(now > r[i]) now = l[i];
            int len = r[i]-l[i]+1;
            for(int j = 1;j <= len && r[i] < sm[1];++j){
                int p = query(1,1,k,r[i]+1);update(1,1,k,r[i]+1);
                int q = query(1,1,k,now);
                fa[p] = q;
                now += 2;
                if(now > r[i]) now = l[i];
            }
        }
    }
    int now = 1;
//    FOR(i,1,k) DEBUG(fa[i]);
    FOR(i,1,k){
        if(fa[i]) ans[i] = ans[fa[i]];
        else ans[i] = str[now++];
    }
    printf("%s\n",ans+1);
    return 0;
}
