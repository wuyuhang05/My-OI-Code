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
#define int long long
const int MAXN = 10 + 5;
const int ha = 998244353;
int map[MAXN][MAXN];
char str[MAXN];
int ans;
bool vis1[MAXN];
bool vis2[MAXN]; // fang

void dfs(int step){
    if(step == 9 + 1){
        ans++;
        if(ans > ha) ans -= ha;
        return;
    }
    FOR(i,1,9){
        if(map[step][i] || vis1[i]) continue;
        int pos = (step-1)/3;pos = pos*3+((i-1)/3)+1;
        if(vis2[pos]) continue;
        vis2[pos] = 1;vis1[i] = 1;
        dfs(step+1);
        vis2[pos] = 0;vis1[i] = 0;
    }
}

const int now = 804434861;

inline void Solve(){
    ans = 0;
    FOR(i,1,9){
        scanf("%s",str+1);
        FOR(j,1,9) map[i][j] = str[j]-'0';
    }
    CLR(vis1,false);CLR(vis2,false);
    dfs(1);
    LL res = now*ans%ha;
    printf("%lld\n",res);
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}