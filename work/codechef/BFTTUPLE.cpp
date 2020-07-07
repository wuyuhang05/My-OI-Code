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

int a[5],b[5];
int ans = 0;

inline void dfs(int x,int y,int z,int step){
    if(std::abs(x) >= 20 || std::abs(y) >= 20 || std::abs(z) >= 20) return;
    if(step == 3) return;
    if(x == b[1] && y == b[2] && z == b[3]){ans = std::min(ans,step);return;}
    int a[23];a[0] = x;a[1] = y;a[2] = z;
    int t[23];FOR(i,0,2) t[i] = a[i];
    FOR(S,0,(1<<3)-1){
        FOR(d,-10,10){
            FOR(i,0,2) a[i] = t[i];
            FOR(i,0,2) if((S>>i)&1) a[i] *= d;
            dfs(a[0],a[1],a[2],step+1);
            FOR(i,0,2) a[i] = t[i];
            FOR(i,0,2) if((S>>i)&1) a[i] += d;
            dfs(a[0],a[1],a[2],step+1);
        }
    }
}

inline void Solve(){
    FOR(i,1,3) scanf("%d",a+i);
    FOR(i,1,3) scanf("%d",b+i);ans = 3;
    dfs(a[1],a[2],a[3],0);
    printf("%d\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
