#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 1e5 + 5;
int c[MAXN],d[MAXN],T;
LL f[MAXN];

int main(){
    FOR(i,0,3) scanf("%d",c+i);
    f[0] = 1ll;scanf("%d",&T);
    FOR(i,0,3){
        FOR(j,c[i],MAXN-1){
            f[j] += f[j-c[i]];
        }
    }
    while(T--){
        FOR(i,0,3) scanf("%d",d+i);
        int s;scanf("%d",&s);
        LL ans = f[s];
        FOR(S,1,(1<<4)-1){
            int now = s,k=0;
            for(int t = S,j=0;t;t>>=1,++j){
                if(t&1) k^=1,now -= (d[j]+1)*c[j];
            }
            if(now >= 0) ans += f[now]*(k?-1:1);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
