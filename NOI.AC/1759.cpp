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

const int MAXN = 1e5 + 5;
const int MAXM = 14348907+23;
const int ha = 998244353;
int a[MAXN],n,m;
int pw[16];
int pw2[MAXN],lw[MAXM],trans[MAXM];

namespace Subtask1{
//public:
    int g[MAXN],h[MAXM];
    inline void Solve(){
        FOR(i,1,n){
            int x = 0;
            FOR(j,0,m-1) x = x*3+((a[i]>>j)&1);
            h[x]++;
        }
        FOR(S,0,pw[m]-1){
            if(lw[S] == -1) continue;
            int x = S-pw[lw[S]],y = x-pw[lw[S]];
            h[S] = (h[x]+h[y])%ha;
        }
        FOR(S,0,pw[m]-1) (g[trans[S]] += pw2[h[S]]) %= ha;
//        FOR(S,0,(1<<m)-1) DEBUG(g[S]);
        int ans = 0;
        FOR(S,1,(1<<m)-1){
            int res = (pw2[n]+1)%ha;
            for(int T = S;T;T = (T-1)&S){
                int t = (g[T]+1)%ha;
                if(__builtin_popcount(T)&1) t = ha-t;
                (res += t) %= ha;
            }
            ans ^= res;
        }
        printf("%d\n",ans);
    }
};

char str[233];
int main(){
    pw[0] = 1;FOR(i,1,15) pw[i] = 3*pw[i-1];
    pw2[0] = 1;FOR(i,1,MAXN-1) pw2[i] = 2ll*pw2[i-1]%ha;
    lw[0] = -1;FOR(i,1,MAXM-1) lw[i] = i%3 == 2 ? 0 : (lw[i/3]==-1 ? -1 : lw[i/3] + 1);
    FOR(i,0,MAXN-1) (pw2[i] += ha-1) %= ha;
    scanf("%d%d",&n,&m);
    trans[0] = trans[1] = (1<<m)-1;
    FOR(i,2,MAXM-1){
        if(lw[i] == -1) trans[i] = (1<<m)-1;
        else{
            trans[i] = trans[i-2*pw[lw[i]]]^(1<<lw[i]);
        }
    }
    FOR(i,1,n){
        scanf("%s",str);
        FOR(j,0,m-1) if(str[j] == '1') a[i] |= (1<<j);
    }
    Subtask1::Solve();
    return 0;
}
