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
const int ha = 10007;
#define lc (x<<1)
#define rc (x<<1|1)
LL s1[MAXN<<2],s2[MAXN<<2],s3[MAXN<<3],tag1[MAXN<<2],tag2[MAXN<<2];
// tag1:add tag2:mul
int n,m;

inline void mul(LL &a,LL b){
    b %= ha;
    a *= b;a %= ha;
}

inline void add(LL &a,LL b){
    (a += b);a %= ha;
}

inline void pushup(int x){
    s1[x] = (s1[lc]+s1[rc])%ha;
    s2[x] = (s2[lc]+s2[rc])%ha;
    s3[x] = (s3[lc]+s3[rc])%ha;
}

inline void pushdown(int x,int l,int r){
    int mid = (l + r) >> 1;
    if(tag2[x] != 1){
        LL a = tag2[x]%ha;
        mul(tag1[lc],a);mul(tag1[rc],a);
        mul(tag2[lc],a);mul(tag2[rc],a);
        mul(s1[lc],a);mul(s1[rc],a);
        mul(s2[lc],a*a);mul(s2[rc],a*a);
        mul(s3[lc],a*a*a);mul(s3[rc],a*a*a);
        tag2[x] = 1;
    }
    if(tag1[x]){
        LL a = tag1[x]%ha;
        add(tag1[lc],a);add(tag1[rc],a);
        add(s3[lc],3*a*s2[lc]+3*a*a*s1[lc]+a*a*a*(mid-l+1));add(s3[rc],3*a*s2[rc]+3*a*a*s1[rc]+a*a*a*(r-mid));
        add(s2[lc],2*a*s1[lc]+a*a*(mid-l+1));add(s2[rc],2*a*s1[rc]+a*a*(r-mid));
        add(s1[lc],a*(mid-l+1));add(s1[rc],a*(r-mid));
        tag1[x] = 0;
    }
}

inline void build(int x,int l,int r){
    tag2[x] = 1;s1[x] = s2[x] = s3[x] = tag1[x] = 0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
}

inline void modify(int x,int l,int r,int L,int R,LL b,int opt){
    if(L <= l && r <= R){
        LL a,c;
        if(opt == 1){
            a = 1;c = b;
            add(tag1[x],b);
        }
        else if(opt == 2){
            a = b;c = 0;
            mul(tag2[x],b);mul(tag1[x],b);
        }
        else{
            a = 0;c = b;
            tag2[x] = 0;tag1[x] = b;
        }
        s3[x] = (a*a*a*s3[x] + 3*a*a*c*s2[x] + 3*a*c*c*s1[x] + c*c*c*(r-l+1)) % ha;
        s2[x] = (a*a*s2[x] + 2*a*c*s1[x] + c*c*(r-l+1)) % ha;
        s1[x] = (a*s1[x] + c*(r-l+1)) % ha;return;
    }
    pushdown(x,l,r);
    int mid = (l + r) >> 1;
    if(L <= mid) modify(lc,l,mid,L,R,b,opt);
    if(R > mid) modify(rc,mid+1,r,L,R,b,opt);
    pushup(x);
}

inline LL query(int x,int l,int r,int L,int R,int opt){
    if(L <= l && r <= R){
        return opt == 1 ? s1[x]%ha : (opt == 2 ? s2[x]%ha : s3[x]%ha);
    }
    pushdown(x,l,r);
    int mid = (l + r) >> 1;LL ans = 0;
    if(L <= mid) add(ans,query(lc,l,mid,L,R,opt));
    if(R > mid) add(ans,query(rc,mid+1,r,L,R,opt));
    return ans;
}

inline void Solve(){
    build(1,1,n);
    FOR(i,1,m){
        LL opt,l,r,c;scanf("%lld%lld%lld%lld",&opt,&l,&r,&c);
        if(opt == 4){
            printf("%lld\n",query(1,1,n,l,r,c));
            continue;
        }
        modify(1,1,n,l,r,c,opt);
    }

}

int main(){
    while(scanf("%d%d",&n,&m) && (n+m)) Solve();
    return 0;
}
