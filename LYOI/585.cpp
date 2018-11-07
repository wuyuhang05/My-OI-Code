#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 300000 + 5;
int N;
std::pair<int,int> a[MAXN];
int f[20][MAXN];

inline void pre(){
    FOR(i,1,N) f[0][i] = a[i].second;
  //  FOR(i,1,N) DEBUG(f[0][i]);
    int log2N = log2(N);
    FOR(i,1,18) for(int j = 1;j+(1<<i)-1 <= N;j++) f[i][j] = std::min(f[i-1][j],f[i-1][j+(1<<i-1)]);
}

inline int calc(int l,int r){
    int c = log2(r-l+1);
    return std::min(f[c][l],f[c][r-(1<<c)+1]);
}

LL ans[MAXN],p[MAXN];

inline void Solve(int l,int r,int d){
    if(l > r) return; 
    int pos = calc(l,r); // min timeset
//    DEBUG(l*100+r*10+pos);
    ans[pos] = d;
    Solve(l,p[pos]-1,d+1);Solve(p[pos]+1,r,d+1);
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N) scanf("%d",&a[i].first),a[i].second = i;
    std::sort(a + 1,a + N + 1);pre();
    FOR(i,1,N) p[a[i].second] = i; // pos[i] 排名为 i 的数的位置
//    FOR(i,1,N) printf("%d ",a[i].second);puts("");
    Solve(1,N,0);
    FOR(i,1,N) printf("%lld\n",ans[i]+=ans[i-1]);
    return 0;
}
