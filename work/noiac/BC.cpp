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

const int MAXN = 11;
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
int opt[MAXN];
int n,l;
LL t[MAXN];int x[MAXN],y[MAXN];

inline bool chk(){
    int sx=0,sy=0;
    FOR(i,1,l) sx += dx[opt[i]],sy += dy[opt[i]];
    FOR(i,1,n){
        LL xx=0,yy=0,t = ::t[i];
        xx = sx*(t/l);yy = sy*(t/l);
        t %= l;
        FOR(j,1,t) xx += dx[opt[j]],yy += dy[opt[j]];
        if(xx != x[i] || yy != y[i]) return 0;
    }
    return 1;
}
int ans = 0;
inline void dfs(int step){
    if(step == l+1){
        ans += chk();
        return;
    }
    FOR(i,0,3) opt[step] = i,dfs(step+1);
}

int main(){
    scanf("%d%d",&n,&l);
    FOR(i,1,n) scanf("%lld%d%d",t+i,x+i,y+i);
    dfs(1);
    printf("%d\n",ans);
    return 0;
}
