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
#define int LL
int n;
std::map<int,int> S;
inline int query(int x){
    S[x] = 1;
    printf("? %lld\n",x);std::fflush(stdout);
    int res;scanf("%lld",&res);return res;
}

int now;

inline bool chk(int x){
    DEBUG(x);
    int t = now;
    if(now+x <= n) {now += x;return query(t+x);}
    {now -= x;return query(t-x);}
}

inline void Solve(){
    scanf("%lld",&n);S.clear();
    now = (((1+n)>>1)+1+n)>>1;
    if(n & 1) now--;
    query(now);
    LL l = 1,r = n-1,ans = n;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) ans = mid,r = mid-1;// >= 
        else l = mid+1;
    }
    printf("= %lld\n",ans);std::fflush(stdout);
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

