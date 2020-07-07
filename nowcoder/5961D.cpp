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

const int MAXN = 2e5 + 5;
const int ha = 1e9 + 7;

bool p[MAXN];
int prime[MAXN],cnt;

inline void prework(){
    FOR(i,2,MAXN-1){
        if(!p[i]) prime[++cnt] = i;
        for(int j = 1;j <= cnt && i*prime[j] < MAXN;++j){
            p[i*prime[j]] = 1;
            if(!(i%prime[j])) break;
        }
    }
}

std::pair<double,LL> f[MAXN];
double Log[MAXN];

int main(){
    prework();
    FOR(i,1,MAXN-1) Log[i] = log(i);
    f[0] = MP(0,1);
    int n;scanf("%d",&n);
    int ps = 0,sm = 0;
    FOR(i,1,cnt){
        sm += prime[i];
        if(sm > n){
            ps = i;break;
        }
    }
    FOR(i,1,ps){
        if(prime[i] > n) break;
        ROF(j,n,prime[i]){
            for(int p = prime[i],k = 1,s = p;s <= j;p*=prime[i],k++,s += p){
                f[j] = std::max(f[j],MP(f[j-s].fi+Log[k+1],f[j-s].se*(k+1)%ha));
            }
        }
    }
    std::pair<double,LL> ans = MP(0,1);
    FOR(i,0,n) ans = std::max(ans,f[i]);
    printf("%lld\n",ans.se);
    return 0;
}
