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

const int ha = 1e7+19;
const int MAXQ = 1e5+5;
const int MAXT = 105;

struct Query{
    int opt,pos;LL val;
}qu[MAXQ];
int stk[MAXQ*MAXT];
LL fac[ha+5],inv[ha+5];
LL v[MAXQ],t;
std::vector<int> p;

inline int calc(int x){
    return std::lower_bound(all(p),x)-p.begin()+1;
}

int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int n,q;
LL ans;

int main(){
    scanf("%d%d",&n,&q);
    fac[0] = 1;
    FOR(i,1,ha-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[ha-1] = qpow(fac[ha-1],ha-2);
    ROF(i,ha-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    FOR(i,1,ha-1) inv[i] = 1ll*inv[i]*fac[i-1]%ha;
    FOR(i,1,q){
        scanf("%d",&qu[i].opt);
        if(qu[i].opt == 1 || qu[i].opt == 5){
            scanf("%d",&qu[i].pos);
            p.pb(qu[i].pos);
        }
        if(qu[i].opt <= 4) scanf("%lld",&qu[i].val),qu[i].val = (qu[i].val%ha+ha)%ha;
        if(qu[i].opt == 3 && !qu[i].val) qu[i].opt = 4;
    }
    std::sort(all(p));
    p.erase(std::unique(all(p)),p.end());
    FOR(i,1,q)
        if(qu[i].opt == 1 || qu[i].opt == 5)
            qu[i].pos = calc(qu[i].pos);
    LL taga = 0ll,tagb = 1ll,sum = 0ll,ans = 0ll;
    scanf("%lld",&t);
    int top = 0;
    FOR(i,1,t){
        LL aa,bb;scanf("%lld%lld",&aa,&bb);
        FOR(j,1,q){
            LL id = (aa+j*bb)%q+1;
            if(qu[id].opt == 1){
                stk[++top] = qu[id].pos;
                LL val = (qu[id].val-taga+ha)%ha*inv[tagb]%ha;
                sum = (sum-(1ll*v[qu[id].pos]*tagb%ha+taga)%ha+ha)%ha;
                v[qu[id].pos] = val;
                sum = (sum+qu[id].val)%ha;
            }
            if(qu[id].opt == 2){
                taga = (taga+qu[id].val)%ha;
                sum = (sum+1ll*qu[id].val*n%ha)%ha;
            }
            if(qu[id].opt == 3){
                tagb = 1ll*tagb*qu[id].val%ha;
                taga = 1ll*taga*qu[id].val%ha;
                sum = 1ll*sum*qu[id].val%ha;
            }
            if(qu[id].opt == 4){
                while(top) v[stk[top]] = 0,stk[top--] = 0;
                taga = qu[id].val,tagb = 1ll;
                sum = 1ll*taga*n%ha;
            }
            if(qu[id].opt == 5){
                LL t = (1ll*v[qu[id].pos]*tagb%ha+taga)%ha;
                ans = (ans+t)%ha;
            }
            if(qu[id].opt == 6){
                ans = (ans+sum)%ha;
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
