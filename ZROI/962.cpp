/*
 * Author: RainAir
 * Time: 2019-09-17 16:28:12
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

const int MAXN = 1e5 + 5;

inline char nc(){
    #define SIZE 100000+3
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

struct MAP{
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)
    int mx[MAXN<<2],mn[MAXN<<2],val[MAXN];

    inline void pushup(int x){
        mx[x] = std::max(mx[lc],mx[rc]);
        mn[x] = std::min(mn[lc],mn[rc]);
    }

    inline void update(int x,int l,int r,int p,int d){
        if(l == r){
            mx[x] = mn[x] = val[l] = d;
            return;
        }
        int mid = (l + r) >> 1;
        p <= mid ? update(lc,l,mid,p,d) : update(rc,mid+1,r,p,d);
        pushup(x);
    }

    inline int calc1(int x,int l,int r,int L,int R,int v){ // <--
        if(mx[x] < v) return -1;
        if(l == r) return l;
        int mid = (l + r) >> 1;
        if(R <= mid) return calc1(lc,l,mid,L,R,v);
        if(L > mid) return calc1(rc,mid+1,r,L,R,v);
        int ans = calc1(lc,l,mid,L,mid,v);
        if(ans != -1) return ans;
        return calc1(rc,mid+1,r,mid+1,R,v);
    }

    inline int calc2(int x,int l,int r,int L,int R,int v){ // -->
        if(mx[x] < v) return -1;
        if(l == r) return l;
        int mid = (l + r) >> 1;
        if(R <= mid) return calc2(lc,l,mid,L,R,v);
        if(L > mid) return calc2(rc,mid+1,r,L,R,v);
        int ans = calc2(rc,mid+1,r,mid+1,R,v);
        if(ans != -1) return ans;
        return calc2(lc,l,mid,L,mid,v);
    }

    inline int calc3(int x,int l,int r,int L,int R){
        if(l == L && r == R) return mn[x];
        int mid = (l + r) >> 1;
        if(R <= mid) return calc3(lc,l,mid,L,R);
        if(L > mid) return calc3(rc,mid+1,r,L,R);
        return std::min(calc3(lc,l,mid,L,mid),calc3(rc,mid+1,r,mid+1,R));
    }
}row,col;
// 记单词：行是 row，列是column（

int n,m,q;

inline bool chk1(int a,int b,int c,int d,int v){ // 井
    if(row.val[a] >= v && col.val[d] >= v) return true;
    if(row.val[c] >= v && col.val[b] >= v) return true;
    return false;
}

inline int chk2(int a,int b,int c,int d,int v){ // Z
    int __ = 1e9;
    if(b > d) std::swap(a,c),std::swap(b,d);
    if(row.val[a] >= v && row.val[c] >= v){ // 两行夹一列
         int _ = col.calc1(1,1,m,b,d,v);
         if(_ != -1) return std::abs(a-c)+std::abs(b-d);
         _ = col.calc2(1,1,m,1,b,v);
         if(_ != -1) __ = std::min(__,std::abs(b-_)+std::abs(a-c)+std::abs(d-_));
         _ = col.calc1(1,1,m,d,m,v);
         if(_ != -1) __ = std::min(__,std::abs(b-_)+std::abs(a-c)+std::abs(d-_));
    }
    if(a > c) std::swap(a,c),std::swap(b,d);
    if(col.val[b] >= v && col.val[d] >= v){
        int _ = row.calc1(1,1,n,a,c,v);
        if(_ != -1) return std::abs(a-c)+std::abs(b-d);
        _ = row.calc2(1,1,n,1,a,v);
        if(_ != -1) __ = std::min(__,std::abs(a-_)+std::abs(b-d)+std::abs(c-_));
        _ = row.calc1(1,1,n,c,n,v);
        if(_ != -1) __ = std::min(__,std::abs(a-_)+std::abs(b-d)+std::abs(c-_));
    }
    return __;
}

inline bool chk3(int a,int b,int c,int d,int v){
    if(a > c) std::swap(a,c);
    if(b > d) std::swap(b,d);
    if(row.calc3(1,1,n,a,c) >= v) return true;
    if(col.calc3(1,1,m,b,d) >= v) return true;
    return false;
}

int main(){
    read(n);read(m);read(q);
    FOR(i,1,q){
        int opt;read(opt);
        int a;read(a);
        if(opt == 1) row.update(1,1,n,a,i);
        if(opt == 2) col.update(1,1,m,a,i);
        if(opt == 3){
            int b,c,d,v;read(b);read(c);read(d);read(v);
            if(a == c && b == d){
                puts("0");
                continue;
            }
            v = i-v;
            if(chk1(a,b,c,d,v) || chk3(a,b,c,d,v)){
                printf("%d\n",std::abs(a-c)+std::abs(b-d));
                continue;
            }
            int ans = chk2(a,b,c,d,v);
            printf("%d\n",ans == 1e9 ? -1 : ans);
        }
    }
    return 0;
}
