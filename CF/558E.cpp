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

const int MAXN = 20;
LL f[MAXN][1<<MAXN],mp[MAXN];
int n,m;
LL ans;

inline int calc(int x){
    FOR(i,0,n-1) if(x&(1<<i)) return i;
    return -1;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);--u;--v;
        mp[u] |= (1<<v);mp[v] |= (1<<u);
    }
    FOR(i,0,n-1) f[i][1<<i] = 1;
    FOR(S,1,(1<<n)-1){
        FOR(i,0,n-1){
            LL fi = calc(S);
            if(S&(1<<fi) && (1<<fi)&mp[i]) ans += f[i][S];
            FOR(j,fi,n-1){
                if(i == j || !((1<<j)&mp[i]) || (1<<j)&S) continue;
                f[j][S|(1<<j)] += f[i][S];
            }
        }
    }
    ans -= m;ans /= 2;
    printf("%lld\n",ans);
    return 0;
}
