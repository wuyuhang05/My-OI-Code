/*
 * Author: RainAir
 * Time: 2019-10-24 14:37:39
 */
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 5000+5;
const int MAXM = 2e7+5;
const int ha = 998244353;
int cf[MAXM];
int n,m,v[MAXN],l[MAXN],r[MAXN];

inline void add(int &a,int b){
    a += b;
    while(a >= ha) a -= ha;
    while(a < 0) a += ha;
}

signed main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n) scanf("%lld%lld%lld",v+i,l+i,r+i);
    FOR(i,1,n){
        FOR(j,i+1,n){
     //       bool flag = r[i]-l[i]+1 < r[j]-l[j]+1;
       //     if(flag) std::swap(r[i],r[j]),std::swap(l[i],l[j]),std::swap(v[i],v[j]);
            int gx = 1ll*v[i]*v[j]%ha;
            /*if(r[i]-l[i] == r[j]-l[j]) R--;
            ggx = 1ll*(R-L+1)*gx%ha;
            (cf[L] += gx) %= ha,(cf[R+1] += ha-gx) %= ha,
            (cf[R+1] += ha-ggx) %= ha,(cf[R+2] += ggx) %= ha;
            L = l[i]+r[j]+1,R = r[i]+l[j]-1;
            ggx = 1ll*(r[j]-l[j]+1)*gx%ha;
            if(L <= R) (cf[L] += ggx) %= ha,(cf[L+1] += ha-ggx) %= ha,(cf[R+1] += ha-ggx) %= ha,(cf[R+2] += ggx) %= ha;
            L = r[i]+l[j],R = r[i]+r[j];
            ggx = 1ll*(R-L+1)*gx%ha;
            (cf[L] += ggx) %= ha;(cf[L+1] += ha-ggx) %= ha;
            (cf[L+1] += ha-gx) %= ha;(cf[R+2] += gx) %= ha;
            if(flag) std::swap(r[i],r[j]),std::swap(l[i],l[j]),std::swap(v[i],v[j]);
            */
            add(cf[l[i]+l[j]],gx);add(cf[l[i]+r[j]+1],ha-gx);
            add(cf[r[i]+l[j]+1],ha-gx);add(cf[r[i]+r[j]+2],gx);
   //         if(flag) std::swap(r[i],r[j]),std::swap(l[i],l[j]),std::swap(v[i],v[j]);
        }
    }
    FOR(i,1,MAXM-1) (cf[i] += cf[i-1]) %= ha;
    FOR(i,1,MAXM-1) (cf[i] += cf[i-1]) %= ha;
    FOR(i,1,m){
        int x;scanf("%lld",&x);
        printf("%lld\n",cf[x]);
    }
    return 0;
}

