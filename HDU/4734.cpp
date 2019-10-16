/*
 * Author: RainAir
 * Time: 2019-10-07 20:52:17
 */
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

const int MAXN = 10+2;
const int MAXM = 5e3 + 5;
int cs = 0;
int f[MAXN][MAXM];
int a[MAXN],len,lim;
int pw[MAXN];
/*
inline int dfs(int i,int j,int flag,int zero){
    if(j < 0) return 0;
    if(!j) return 1;
    if(!i) return 0;
    if(!flag) if(f[i][lim-j] != -1) return f[i][lim-j];
    int ans = 0;
    if(flag){
        FOR(x,0,a[i]-1){
            if(zero && !x) ans += dfs(i-1,j,0,1);
            else ans += dfs(i-1,j-pw[i]*x,0,0);
        }
        if(zero && !a[i]) ans += dfs(i-1,j,1,1);
        else ans += dfs(i-1,j-pw[i]*a[i],1,0);
    }
    else{
        FOR(x,0,9){
            if(zero && !x) ans += dfs(i-1,j,0,1);
            else ans += dfs(i-1,j-pw[i]*x,0,0);
        }
    }
    if(!flag) f[i][lim-j] = ans;
    return ans;
}*/

inline int dfs(int i,int j,int flag){
    if(!i) return j <= lim;
    if(j > lim) return 0;
    if(!flag && f[i][lim-j] != -1) return f[i][lim-j];
    int up = flag ? a[i] : 9;
    int ans = 0;
    FOR(x,0,up){
        ans += dfs(i-1,j+pw[i]*x,flag&&(a[i] == x));
    }
    if(!flag) f[i][lim-j] = ans;
    return ans;
}

inline int calc(int x){
    if(x < 0) return 0;
    len = 0;CLR(a,0);
    while(x) a[++len] = x%10,x /= 10;//CLR(f,-1);
    int ans = 0;
    return dfs(len,0,1);
}

inline void Solve(){
    printf("Case #%d: ",++cs);
    int A,B;
    scanf("%d%d",&A,&B);
 //   A = 1e9-cs,B = 1e9-cs;
    lim = 0;int l = 0;
    while(A) lim += (A%10)*pw[++l],A /= 10;
    printf("%d\n",calc(B));
}

int main(){
   // freopen("a.out","w",stdout);
    CLR(f,-1);
    pw[1] = 1;FOR(i,2,MAXN-1) pw[i] = pw[i-1]<<1;
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
