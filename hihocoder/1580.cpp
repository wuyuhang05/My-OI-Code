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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int N,M,P;
float log2N;
const int MAXN = 300+5;
int a[MAXN][MAXN],sum[MAXN][MAXN];
int st[MAXN][MAXN][20];
int ans = 0;

inline void init(int id){
    FOR(j,1,log2N){
        FOR(i,1,N){
            if(i + (1<<j) - 1 > N) break;
            st[id][i][j] = std::min(st[id][i][j-1],st[id][i+(1<<(j-1))][j-1]);
        }
    }
}

inline int calc(int x,int l,int r){
    // DEBUG(l);DEBUG(r);
    int c = log2(r-l+1);
    return std::min(st[x][l][c],st[x][r-(1<<c)+1][c]);
}

inline int query(int a,int b){
    int t[MAXN],f[MAXN][2];
    FOR(i,1,M) t[i] = sum[b][i] - sum[a-1][i];
    // printf("UP:%d DOWN:%d:\n",a,b);
    f[1][0] = t[1],f[1][1] = t[1]-calc(1,a,b)+P;
    int ret = f[1][1];
    if(!(a==1&&b==N) || M>1) ret = std::max(ret,f[1][0]);
    FOR(i,2,M){
        //DEBUG(ret);
        f[i][0] = std::max(f[i-1][0]+t[i],t[i]);
        f[i][1] = std::max(std::max(f[i-1][0],0)+t[i]-calc(i,a,b)+P,std::max(f[i-1][1]+t[i],t[i]));
        // DEBUG(f[i][0]);DEBUG(f[i][1]);DEBUG(t[i]);
        // DEBUG(calc(i,a,b));DEBUG(t[i]);
        ret = std::max(ret,f[i][1]);
        if(i != M || (i == M && !(a == 1 && b == N))) ret = std::max(ret,f[i][0]);
    }
    return ret;
}

inline void Solve(){
    log2N = log2(N);
    ans = INT_MIN;
    CLR(st,0x3f);CLR(sum,0);
    FOR(i,1,N) FOR(j,1,M) scanf("%d",&sum[i][j]),st[j][i][0] = sum[i][j];
    FOR(i,1,N) FOR(j,1,M) sum[i][j] += sum[i-1][j];
    FOR(i,1,M) init(i);
    //ans = query(1,1);
    FOR(i,1,N) FOR(j,i,N) ans = std::max(ans,query(i,j));
    printf("%d\n",ans);
}

int main(){
    while(~scanf("%d%d%d",&N,&M,&P)) Solve();
    return 0;
}