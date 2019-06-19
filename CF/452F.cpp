#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 300000+5;
int a[MAXN],n,p[MAXN];
LL pw[MAXN];
const int ha = 1e9+9;

struct Node{ // Hash Node
    int l,r;
    LL sum,rev;

    Node operator + (const Node &t) const {
        if(l == -1) return t;
        if(t.l == -1) return (*this);
        return (Node){l,t.r,(sum*pw[t.r-t.l+1]%ha+t.sum)%ha,(t.rev*pw[r-l+1]%ha+rev)%ha};
    }
}s[MAXN<<4];

#define lc (x<<1)
#define rc (x<<1|1)

inline void build(int x,int l,int r){
    s[x] = (Node){l,r,0,0};
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    s[x] = s[lc] + s[rc];
}

inline void update(int x,int l,int r,int pos,int val){
    if(l == r){
        s[x].sum = s[x].rev = val;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos,val);
    else update(rc,mid+1,r,pos,val);
    s[x] = s[lc] + s[rc];
}

inline Node query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return s[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    pw[0] = 1;FOR(i,1,n) pw[i] = (pw[i-1]<<1ll)%ha;
    build(1,1,n);
    FOR(i,1,n){
        update(1,1,n,a[i],1);
        if((a[i] << 1) - 1 <= n){
            if(a[i] > 1 && query(1,1,n,1,a[i]-1).sum != query(1,1,n,a[i]+1,(a[i]<<1)-1).rev){
                puts("YES");
                return 0;
            }
        }
        else{
            if(a[i] < n && query(1,1,n,a[i]+1,n).rev != query(1,1,n,(a[i]<<1)-n,a[i]-1).sum){
                puts("YES");
                return 0;
            }
        }
    }
    puts("NO");
    return 0;
}
