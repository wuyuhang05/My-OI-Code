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

const int MAXN = 2e5 + 5;

int n,k,seed,p,m;
int a[MAXN];

int sm[MAXN<<5],lc[MAXN<<5],rc[MAXN<<5],tot,root[MAXN];

inline void insert(int prev,int &v,int l,int r,int p){
    v = ++tot;sm[v] = sm[prev];lc[v] = lc[prev];rc[v] = rc[prev];
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid) insert(lc[prev],lc[v],l,mid,p);
    else insert(rc[prev],rc[v],mid+1,r,p);
}

inline int query(int x,int l,int r,int L,int R){
    if(!x) return -1;
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc[x],l,mid,L,R);
    if(L > mid) return query(rc[x],mid+1,r,L,R);
    int t = query(lc[x],l,mid,L,mid);
    return t==-1 ? query(rc[x],mid+1,r,mid+1,R) : t;
}

std::vector<int> pos[MAXN];

inline void Solve(std::vector<int> ep,int now){
    if(k <= 0) return;
    int ch = 0;
    while(k > 0){
        if(ch == m) return;
        ch = query(root[ep[0]+1],1,m,ch+1,m);
        if(ch == -1) return;
        int nxt = (1ll*now*seed%p+ch)%p;
        int cnt = 0;
        for(auto x:ep){
            cnt += pos[ch].end()-std::upper_bound(all(pos[ch]),x);
        }
        if(cnt < k){
            std::vector<int> S;
            k -= cnt;while(cnt--) printf("%d\n",nxt);
            for(auto x:ep){
                auto u = std::upper_bound(all(pos[ch]),x);
                while(u != pos[ch].end()) S.pb(*u),++u;
            }
            std::sort(all(S));
            Solve(S,nxt);
        }
        else while(k--) printf("%d\n",nxt);
    }
}

int main(){
    scanf("%d%d%d%d",&n,&k,&seed,&p);
    FOR(i,1,n) scanf("%d",a+i),m = std::max(m,a[i]),pos[a[i]].pb(i);
    ROF(i,n,1) insert(root[i+1],root[i],1,m,a[i]);
    Solve(std::vector<int>(1,0),0);
    return 0;
}