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

const int MAXN = 15;
const int ha = 1e9 + 7;
LL pw[MAXN*MAXN];
LL bitcnt[1<<MAXN],ein[1<<MAXN],eout[1<<MAXN],f[1<<MAXN],g[1<<MAXN],h[1<<MAXN],p[1<<MAXN];
int n,m;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        u = 1<<(u-1);v = 1<<(v-1);
        eout[u] |= v;ein[v] |= u;
    }
    pw[0] = 1;
    FOR(i,1,n*n) pw[i] = (pw[i-1]<<1)%ha;
    bitcnt[0] = 0;
    FOR(i,1,(1<<n)-1) bitcnt[i] = bitcnt[(i-(i&-i))] + 1;
    FOR(S,1,(1<<n)-1){
        int one = S&-S,out = S^one;
        for(int i = out;i;i = (i-1)&out)
            g[S] = (g[S] - g[i]*f[S-i]%ha + ha)%ha;
        h[S] = h[out]+bitcnt[ein[one]&out]+bitcnt[eout[one]&out];
        f[S] = pw[h[S]];
        for(int i = S;i;i = (i-1)&S){
            if(i != S){
                int t = (i^S)&-(i^S);
                p[i] = p[i^t]+bitcnt[eout[t]&i]-bitcnt[ein[t]&(i^S)];
            }else p[i] = 0;
            f[S] = (f[S]-pw[h[S^i]+p[i]]*g[i]%ha + ha)%ha;
        }
        g[S] = (g[S]+f[S])%ha;
    }
    printf("%lld\n",(f[(1<<n)-1]+ha)%ha);
    return 0;
}
