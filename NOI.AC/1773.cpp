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

const int MAXN = 5e4 + 5;
const int MAX = 256;

std::vector<int> sx,sy;

struct Tree{
    std::bitset<MAXN> sm[MAXN];
    int lc[MAXN],rc[MAXN],rt,tot,a[MAXN];

    inline void build(int &x,int l,int r){
        x = ++tot;
        if(r-l <= MAX){
            FOR(i,l,r) sm[x].set(a[i]);return;
        }
        int mid = (l + r) >> 1;
        build(lc[x],l,mid);build(rc[x],mid+1,r);
        sm[x] = sm[lc[x]]|sm[rc[x]];
    }

    inline void query(int x,int l,int r,int L,int R,std::bitset<MAXN> &ans){
        if(L <= l && r <= R){
            if(r-l <= MAX) FOR(i,l,r) ans.set(a[i]);
            else ans |= sm[x];
            return;
        }
        int mid = (l + r) >> 1;
        if(L <= mid) query(lc[x],l,mid,L,R,ans);
        if(R > mid) query(rc[x],mid+1,r,L,R,ans);
    }
}T1,T2;

int n;
int x[MAXN],y[MAXN];
std::vector<P> S;
std::vector<int> idx,idy;

int main(){
    read(n);
    FOR(i,1,n){
        read(x[i]);read(y[i]);
        sx.pb(x[i]);sy.pb(y[i]);
    }
    std::sort(all(sx));std::sort(all(sy));

    sx.erase(std::unique(all(sx)),sx.end());sy.erase(std::unique(all(sy)),sy.end());
    FOR(i,1,n) x[i] = std::lower_bound(all(sx),x[i])-sx.begin()+1,
        y[i] = std::lower_bound(all(sy),y[i])-sy.begin()+1;

    FOR(i,1,n) S.pb(MP(x[i],y[i]));std::sort(all(S));
    FOR(i,1,n) T1.a[i] = S[i-1].se,idx.pb(S[i-1].fi);
    for(auto &x:S) std::swap(x.fi,x.se);std::sort(all(S));
    FOR(i,1,n) T2.a[i] = S[i-1].se,idy.pb(S[i-1].fi);S.clear();
    T1.build(T1.rt,1,n);T2.build(T2.rt,1,n);

    int q,T,ansx=0,ansy=0;
    read(q);read(T);
    while(q--){
        int x1,y1,x2,y2;read(x1);read(y1);read(x2);read(y2);
        x1 ^= (ansx*T);x2 ^= (ansx*T);y1 ^= (ansy*T);y2 ^= (ansy*T);
        x1 = std::lower_bound(all(sx),x1)-sx.begin()+1;
        int _x1 = std::lower_bound(all(idx),x1)-idx.begin()+1;
        y1 = std::lower_bound(all(sy),y1)-sy.begin()+1;
        int _y1 = std::lower_bound(all(idy),y1)-idy.begin()+1;
        x2 = std::upper_bound(all(sx),x2)-sx.begin();
        int _x2 = std::upper_bound(all(idx),x2)-idx.begin();
        y2 = std::upper_bound(all(sy),y2)-sy.begin();
        int _y2 = std::upper_bound(all(idy),y2)-idy.begin();
        if(x1 <= x2 && y1 <= y2){
            std::bitset<MAXN> bx,by;
            T1.query(T1.rt,1,n,_x1,_x2,by);T2.query(T2.rt,1,n,_y1,_y2,bx);
            bx >>= x1;by >>= y1;
            bx <<= (x1+MAXN-x2-1);by <<= (y1+MAXN-y2-1);
            ansx = bx.count();ansy = by.count();
        }
        else ansx = ansy = 0;
        printf("%d %d\n",ansx,ansy);
    }
    return 0;
}
