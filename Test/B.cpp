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

const int MAXN = 200000+5;
int N;
int a[MAXN],b[MAXN],p[MAXN];

namespace Subtask1{
    bool vis[MAXN];
    int ans[MAXN],min=INT_MAX;

    inline void dfs(int step,int gx){
        if(step == N+1){
            if(gx < min){
                min = gx;
                FOR(i,1,N) ans[i] = p[i];
            }
            return;
        }
        FOR(i,1,N) if(!vis[i]) vis[i] = true,p[step] = i,dfs(step+1,gx+std::abs(a[step]-b[i])),vis[i] = false;
    }
        
    inline void Solve(){
        dfs(1,0);
        FOR(i,1,N) printf("%d ",ans[i]);puts("");
    }
}

int main(){
    freopen("B.in","r",stdin);
    freopen("B.out","w",stdout);
    scanf("%d",&N);
    FOR(i,1,N) scanf("%d",a+i);
    FOR(i,1,N) scanf("%d",b+i);
    Subtask1::Solve();
    return 0;
}