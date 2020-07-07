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

const int MAXN = 1e6 + 5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)
int mx[MAXN<<2],ans[MAXN<<2],a[MAXN];
std::multiset<int> S[MAXN<<2];

inline int top(int x){
    if(S[x].empty()) return -1e9;
    return *S[x].rbegin();
}

inline void pushup(int x){
    mx[x] = std::max(mx[lc],mx[rc]);
    ans[x] = std::max(top(x)+mx[x],std::max(ans[lc],ans[rc]));
}

inline void build(int x,int l,int r){
    if(l == r){mx[x] = a[l];ans[x] = 0;return;}
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline void update(int x,int l,int r,int pos,int d){
    if(l == r) {mx[x] = d;ans[x] = 0;return;}
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos,d);
    else update(rc,mid+1,r,pos,d);
    pushup(x);
}

inline void modify(int x,int l,int r,int L,int R,int d,int opt){
    if(L > R) return;
    if(l == L && r == R){
        if(opt == 1) S[x].insert(d);
        else S[x].erase(S[x].find(d));
        ans[x] = std::max(top(x)+mx[x],std::max(ans[lc],ans[rc]));
        return;
    }
    int mid = (l + r) >> 1;
    if(R <= mid) modify(lc,l,mid,L,R,d,opt);
    else if(L > mid) modify(rc,mid+1,r,L,R,d,opt);
    else modify(lc,l,mid,L,mid,d,opt),modify(rc,mid+1,r,mid+1,R,d,opt);
    pushup(x);
}

int n,k,q;
int pos[MAXN],x[MAXN];
bool used[MAXN];

int main(){
    scanf("%d%d%d",&n,&k,&q);
    FOR(i,1,n) scanf("%d",a+i);
    build(1,1,n);
    FOR(i,1,q){
        scanf("%d%d",pos+i,x+i);used[pos[i]] = 1;
    }
    int gx = 0;std::deque<int> Q;
    FOR(i,1,n){
        if(used[i]){
            int l = std::max(1,i-k+1),r = std::min(n,i+k-1);
            modify(1,1,n,l,i-1,a[i],1);modify(1,1,n,i+1,r,a[i],1);
            continue;
        }
        while(!Q.empty() && Q.front() <= i-k) Q.pop_front();
        if(!Q.empty()) gx = std::max(gx,a[i]+a[Q.front()]);
        while(!Q.empty() && a[Q.back()] <= a[i]) Q.pop_back();
        Q.pb(i);
    }
    printf("%d\n",std::max(gx,ans[1]));
    FOR(i,1,q){
        int p = pos[i],d = x[i];
        int l = std::max(1,p-k+1),r = std::min(n,p+k-1);
        modify(1,1,n,l,p-1,a[p],-1);modify(1,1,n,p+1,r,a[p],-1);
        a[p] = d;update(1,1,n,p,a[p]);
        modify(1,1,n,l,p-1,a[p],1);modify(1,1,n,p+1,r,a[p],1);
        printf("%d\n",std::max(gx,ans[1]));
    }
    return 0;
}
