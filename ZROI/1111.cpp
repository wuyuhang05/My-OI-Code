/*
 * Author: RainAir
 * Time: 2019-10-05 08:46:45
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
    #define SIZE 300000+5
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;char ch = nc();
    while(!isdigit(ch)) ch = nc();
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
}
 
inline void read(LL &x){
    x = 0;char ch = nc();
    while(!isdigit(ch)) ch = nc();
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
}
 
const int MAXN = 2e5 + 5;
std::vector<double> S;
P a[MAXN],b[MAXN],q[MAXN];
int aa[MAXN],qq[MAXN],x[MAXN];
int n,m,T;

inline bool cmp(const P &a,const P &b){
    return 1ll*b.fi*a.se < 1ll*a.fi*b.se;
}

int sm[MAXN<<2],sm2[MAXN<<2];//,sz[MAXN<<2],cnt[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
    sm[x] = sm[lc] + sm[rc];
    sm2[x] = sm2[lc] + sm2[rc];
//    sz[x] = sz[lc] + sz[rc] + cnt[x];
}

inline void insert(int x,int l,int r,int p,int d,int d2){
    if(l == r){
  //      cnt[x]++;sz[x]++;
        sm[x] += d;
        sm2[x] += d2;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) insert(lc,l,mid,p,d,d2);
    else insert(rc,mid+1,r,p,d,d2);
    pushup(x);
}

inline void del(int x,int l,int r,int p,int d,int d2){
    if(l == r){
        //cnt[x]--;sz[x]--;
        sm[x] -= d;
        sm2[x] -= d2;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) del(lc,l,mid,p,d,d2);
    else del(rc,mid+1,r,p,d,d2);
    pushup(x);
}
/*
inline int query1(int x,int l,int r,int L,int R){
    if(L > R) return 0;
    if(l == L && r == R) return sz[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query1(lc,l,mid,L,R);
    if(L > mid) return query1(rc,mid+1,r,L,R);
    return query1(lc,l,mid,L,mid)+query1(rc,mid+1,r,mid+1,R);
}
*/
inline int query2(int x,int l,int r,int L,int R){
    if(L > R) return 0;
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query2(lc,l,mid,L,R);
    if(L > mid) return query2(rc,mid+1,r,L,R);
    return query2(lc,l,mid,L,mid)+query2(rc,mid+1,r,mid+1,R);
}

inline int query3(int x,int l,int r,int L,int R){
    if(L > R) return 0;
    if(l == L && r == R) return sm2[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query3(lc,l,mid,L,R);
    if(L > mid) return query3(rc,mid+1,r,L,R);
    return query3(lc,l,mid,L,mid)+query3(rc,mid+1,r,mid+1,R);
}

LL ans = 0;

signed main(){
 //   freopen("test.in","r",stdin);
 //   freopen("test1.out","w",stdout);
    read(n);read(m);read(T);
    FOR(i,1,n) read(a[i].fi),read(a[i].se),S.pb(1.0*a[i].fi/a[i].se),b[i] = a[i];
    FOR(i,1,m) read(x[i]),read(q[i].fi),read(q[i].se),S.pb(1.0*q[i].fi/q[i].se);
    std::sort(all(S));
    std::unique(all(S));
    int lim = S.size();
    FOR(i,1,n) aa[i] = std::lower_bound(all(S),1.0*a[i].fi/a[i].se) - S.begin();
    FOR(i,1,m) qq[i] = std::lower_bound(all(S),1.0*q[i].fi/q[i].se) - S.begin();
    FOR(i,1,n) ++aa[i];FOR(i,1,m) ++qq[i];
    std::sort(b+1,b+n+1,cmp);int sm = 0;
    FOR(i,1,n) sm += b[i].se,ans += 1ll*(T-sm)*b[i].fi;
    printf("%lld\n",ans);
    FOR(i,1,n) insert(1,1,lim,aa[i],a[i].fi,a[i].se);
    FOR(i,1,m){
        int prep = x[i];//int d = q[i].se-a[prep].se;
        //delete
        int t = query2(1,1,lim,1,aa[prep])-a[prep].fi;
        ans += 1ll*t*a[prep].se;
        ans -= 1ll*(T-query3(1,1,lim,aa[prep]+1,lim)-a[prep].se)*a[prep].fi;
        //DEBUG(ans);
        del(1,1,lim,aa[prep],a[prep].fi,a[prep].se);
        //DEBUG((T-query3(1,1,lim,aa[prep]+1,lim))*a[prep].fi);
     //   DEBUG(query3(1,1,lim,aa[prep]+1,lim)+a[prep].se);
       // DEBUG(ans);del(1,1,lim,aa[prep],a[prep].fi,a[prep].se);
        aa[prep] = qq[i];a[prep] = q[i];
        insert(1,1,lim,aa[prep],a[prep].fi,a[prep].se);
        t = query2(1,1,lim,1,aa[prep])-a[prep].fi;
        ans -= 1ll*t*a[prep].se;
        ans += 1ll*(T-query3(1,1,lim,aa[prep]+1,lim)-a[prep].se)*a[prep].fi;
        //DEBUG(query3(1,1,lim,aa[prep]+1,lim));
        printf("%lld\n",ans);
    }
    return 0;
}


