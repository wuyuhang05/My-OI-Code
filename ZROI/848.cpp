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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 50000+5;
const int MAXM = 100000+5;
int a[MAXN],n;
std::vector<int> S[MAXM];
std::vector<P> t;

int mx[MAXN<<2];
#define lc (x<<1)
#define rc (x<<1|1)

inline void pushup(int x){
    mx[x] = std::max(mx[lc],mx[rc]);
}

inline void update(int x,int l,int r,int pos,int d){
    if(l == r){
        mx[x] = std::max(mx[x],d);
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos,d);
    else update(rc,mid+1,r,pos,d);
    pushup(x);
}

inline int query(int x,int l,int r,int L,int R){
    if(L > R) return 0;
    if(l == L && r == R) return mx[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return std::max(query(lc,l,mid,L,mid),query(rc,mid+1,r,mid+1,R));
}

inline void Solve(){
    scanf("%d%*d",&n);t.clear();CLR(mx,0);
    FOR(i,1,n) scanf("%d",a+i),S[a[i]].pb(i);
    FOR(i,1,MAXM-5){
        FOR(x,0,(int)S[i].size()-1){
            FOR(y,x,(int)S[i].size()-1){
                t.pb(MP(S[i][x],S[i][y]));
            }
        }
        S[i].clear();
    }
    std::sort(all(t));
    for(auto x:t){
        update(1,1,n,x.se,query(1,1,n,x.se+1,n)+1+(x.fi != x.se));
    }
    printf("%d\n",query(1,1,n,1,n));
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
