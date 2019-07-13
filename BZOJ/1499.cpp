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
#define P std::pair<int,int>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200+5;
const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

int n,m,sx,sy,k,now,ans;
char str[MAXN][MAXN];
int f[2][MAXN][MAXN];
P q[MAXN];// pair<val,pos>

inline void calc(int x,int y,int len,int d){
    d--;int head = 1,tail = 0;
    for(int i = 1;x >= 1 && x <= n && y >= 1 && y <= m;x += dx[d],y += dy[d],++i){
        if(str[x][y] == 'x') {head = 1,tail = 0;continue;}
        while(head <= tail && q[tail].fi + i - q[tail].se < f[now^1][x][y]) tail--;
        q[++tail] = MP(f[now^1][x][y],i);
        if(q[tail].se - q[head].se > len) head++;
        f[now][x][y] = q[head].fi + i - q[head].se;
        ans = std::max(ans,f[now][x][y]);
    }
}

int main(){
    scanf("%d%d%d%d%d",&n,&m,&sx,&sy,&k);
    FOR(i,1,n) scanf("%s",str[i]+1);CLR(f,0xf3);
    f[now][sx][sy] = 0;
    while(k--){
        now ^= 1;int l,r,d;scanf("%d%d%d",&l,&r,&d);
        if(d == 1) FOR(i,1,m) calc(n,i,r-l+1,d);
        if(d == 2) FOR(i,1,m) calc(1,i,r-l+1,d);
        if(d == 3) FOR(i,1,n) calc(i,m,r-l+1,d);
        if(d == 4) FOR(i,1,n) calc(i,1,r-l+1,d);
    }
    printf("%d\n",ans);
    return 0;
}
