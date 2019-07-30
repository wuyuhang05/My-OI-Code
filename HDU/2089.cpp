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

const int MAXN = 30;
int p[MAXN],cnt,pw[MAXN];

inline void calc(int x){
    cnt = 0;
    if(!x) p[cnt++] = x;
    while(x) p[cnt++] = x%10,x /= 10;
}

inline int get(int pos){
    int res = 0;
    ROF(i,pos,0) res = res*10+p[i];
    return res + 1;
}

int f[MAXN][2];

inline int dfs(int pos,int pre,int sta,int lim){
    if(pos == -1) return 1;
    if(!lim && f[pos][sta] != -1) return f[pos][sta];
    int res = 0,ed = lim ? p[pos] : 9;
    FOR(i,0,ed){
        if(pre == 6 && i == 2) continue;
        if(i == 4) continue;
        res += dfs(pos-1,i,i == 6,lim&&i == p[pos]);
    }
    if(!lim) f[pos][sta] = res;
    return res;
}

inline int solve(int x){
    calc(x);return dfs(cnt-1,0,0,1);   
}

int main(){
    int l,r;CLR(f,-1);
    pw[0] = 1;FOR(i,1,25) pw[i] = 1ll*pw[i-1]*10;
    while(~scanf("%d%d",&l,&r) && (l+r)){
        int ans = solve(r)-solve(l-1);
        printf("%d\n",ans);
    }
    return 0;
}
