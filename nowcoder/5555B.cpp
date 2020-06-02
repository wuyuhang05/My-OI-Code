#include<bits/stdc++.h>

#define fi first
#define se second
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

const int MAXN = 1e6 + 5;
const int MAXB = (1<<16)-1;
const int ha = 998244353;

U LL G(U LL x) {
    x^=x<<13;
    x^=x>>7;
    x^=x<<17;
    return x;
}

int n,m;
U LL q[MAXN],a[MAXN];
std::vector<U LL> S[MAXB+233];
bool ans[MAXN];

inline int pc(U LL x){
    int res = 0;
    while(x) res += __builtin_popcount(x&MAXB),x >>= 16;
    return res;
}

int main(){
    scanf("%d%d",&n,&m);scanf("%llu",a+1);
    FOR(i,2,n) a[i] = G(a[i-1]);
    FOR(i,1,m) scanf("%llu",q+i);
    FOR(cs,0,3){
        FOR(i,0,MAXB) S[i].clear();
        FOR(i,1,n) S[(a[i]>>(cs*16))&MAXB].pb(a[i]);
        FOR(i,1,m){
            if(ans[i]) continue;
            for(auto x:S[(q[i]>>(cs*16))&MAXB]){
                if(pc(x^q[i]) <= 3){
                    ans[i] = 1;break;
                }
            }
        }
    }
    int res = 0;
    FOR(i,1,m) res = (2ll*res%ha+ans[i])%ha;
    printf("%d\n",res);
    return 0;
}
