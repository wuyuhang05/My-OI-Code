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

const int dx[10] = {0,-1,0,1,-1,0,1,-1,0,1};
const int dy[10] = {0,-1,-1,-1,0,0,0,1,1,1};

//-1,-1
//0,-1
//1,-1
//-1,0
//0,0
//1,0
//-1,1
//0,1
//1,1
const int MAXN = 1000000+5;
struct pt{
    LL x,y;
    pt(){}
    pt(LL x,LL y) : x(x),y(y) {}

    inline pt operator - (const pt &t) const {
        return pt(x-t.x,y-t.y);
    }

    inline LL operator * (const pt &t) const {
        return x*t.y-y*t.x;
    }
}S,T;

char str[MAXN+12];
int n;

LL myabs(LL x){
    return x < 0 ? -x : x;
}

inline void Solve(){
    scanf("%s",str+1);n = strlen(str+1);
    pt pre,now;now = pt(0,0);LL ans = 0;S = T = pt(0,0);
    FOR(i,1,n-1){
        int x = str[i]-'0';
        pre = now;now  = pt(pre.x+dx[x],pre.y+dy[x]);
        if(i == 1) S = now;if(i == n) T = now;
        ans += pre*now;
        //a[i] = pt(a[i-1].x+dx[x],a[i-1].y+dy[x]);
    }
    ans += (S*T);
    ans = myabs(ans);
    printf("%lld",ans/2);
    if(ans&1) printf(".5");
    puts("");
}

int main(){
 //   freopen("a.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
