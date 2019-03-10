#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000+5;

int sum[MAXN<<4],lc[MAXN<<4],rc[MAXN<<4],root[MAXN],cnt;

inline int New(int lc,int rc,int sum){
    ::sum[++cnt] = sum;::lc[cnt] = lc;::rc[cnt] = rc;
    return cnt;
}

inline int insert(int prev,int l,int r,int pos){
    int v = New(lc[prev],rc[prev],sum[prev]);
    if(l == r){
        sum[v]++;return v;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) lc[v] = insert(lc[prev],l,mid,pos);
    else rc[v] = insert(rc[prev],mid+1,r,pos);
    sum[v]++;return v;
}
int x,y;
inline int query(int L,int R,int l,int r){
    if(x>y) return 0;
    if(x <= l && r <= y) return sum[R]-sum[L];
    int mid = (l + r) >> 1,res = 0;
    if(x <= mid) res += query(lc[L],lc[R],l,mid);
    if(y > mid) res += query(rc[L],rc[R],mid+1,r);
    return res;
}

int a[MAXN],num[MAXN],nn,n,m;

inline void init(){
    cnt = 0;CLR(lc,0);CLR(rc,0);CLR(sum,0);CLR(root,0);nn = 0;CLR(num,0);
}

inline void Solve(){
    init();
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i),num[nn++] = a[i];
    std::sort(num,num+nn);
    nn = std::unique(num,num+nn)-num;
    FOR(i,1,n){
        int x = std::lower_bound(num,num+nn,a[i])-num;
        root[i] = insert(root[i-1],0,nn-1,x);
    }
    while(m--){
        int a,b,c;scanf("%d%d%d",&a,&b,&c);
        x = 0;y = std::upper_bound(num,num+nn,c)-num-1;
        printf("%d\n",query(root[a],root[b+1],0,nn-1));
    }
}

int main(){
    int T;scanf("%d",&T);
    FOR(i,1,T) printf("Case %d:\n",i),Solve();
    return 0;
}