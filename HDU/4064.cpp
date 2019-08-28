/*
 * Author: RainAir
 * Time: 2019-08-25 16:32:19
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e6 + 5;
const int ha = 1000000007;
int f[2][MAXN],pw[MAXN],now;
int n,m,mul = 1,cs;
char s[20][20][5];
std::map<char,int> bg;

inline void dfs(int t,int step,int up,int down,int right){
    if(step > m){
        if(t == 1) (f[now^1][down] += mul) %= ha;
        else (f[now^1][down] += 1ll*mul*f[now][up]%ha) %= ha;
        return;
    }
    bool flag = true;
    FOR(i,1,3) if(s[t][step][i] != s[t][step][0]) {flag = false;break;}
    if(flag){
        mul *= 4;
        int x = bg[s[t][step][0]];
        if(right == -1 || right == x)
            dfs(t,step+1,up*3+x,down*3+x,x);
        mul /= 4;
        return;
    }
    FOR(i,0,3){
        int u = bg[s[t][step][i]];
        int r = bg[s[t][step][(i+1)%4]];
        int d = bg[s[t][step][(i+2)%4]];
        int l = bg[s[t][step][(i+3)%4]];
        if(right == -1 || right == l)
            dfs(t,step+1,up*3+u,down*3+d,r);
    }
}

inline void Solve(){
    scanf("%d%d",&n,&m);now = 0;CLR(f,0);mul = 1;
    FOR(i,1,n) FOR(j,1,m) scanf("%s",s[i][j]);
    FOR(i,1,n){
        CLR(f[now^1],0);
        dfs(i,1,0,0,-1);
        now ^= 1;
    }
    LL ans = 0;
    FOR(i,0,pw[m]-1){
        (ans += f[now][i]) %= ha;
    }
    printf("Case %d: %lld\n",++cs,ans);
}

int main(){
    bg['C'] = 0,bg['R'] = 1;bg['F'] = 2;
    pw[0] = 1;FOR(i,1,12) pw[i] = pw[i-1]*3;
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
