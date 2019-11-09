/*
 * Author: RainAir
 * Time: 2019-11-07 08:22:34
 */
#pragma GCC optimize("Ofast")
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
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3000 + 5;
int n,ha;
std::vector<int> a;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

std::map<int,int> S;
int nxt[MAXN],inv[MAXN],pre[MAXN],prei[MAXN];
std::map<int,int> p;
int b[MAXN];

inline void init(){
    FOR(i,0,n) b[i+1] = a[i]%ha;
    pre[0] = 1;
    FOR(i,1,n+1) pre[i] = 1ll*pre[i-1]*b[i]%ha;
    prei[n+1] = qpow(pre[n+1]);
    ROF(i,n,1) prei[i] = 1ll*prei[i+1]*b[i+1]%ha;
    FOR(i,1,n+1) inv[i] = 1ll*prei[i]*pre[i-1]%ha;
    FOR(i,0,n) inv[i] = inv[i+1];
}

int main(){
    freopen("awesome.in","r",stdin);
    freopen("awesome.out","w",stdout);
    scanf("%d%d",&n,&ha);
    FOR(i,1,n){
        int x;scanf("%d",&x);
        if(x%ha) a.pb(x);//,p[x]++;
    }
    n = a.size()-1;
    std::sort(all(a));
    int lst = n+1;
    nxt[n+1] = n+1;
    ROF(i,n,1){
        nxt[i] = lst;
        if(a[i] != a[i-1]) lst = i;
    }
    nxt[0] = lst;
 //   FOR(i,0,n) DEBUG(nxt[i]);
    //FOR(i,0,n) inv[i] = qpow(a[i]%ha);
    init();
//    FOR(i,0,n) assert(inv[i] == qpow(a[i]%ha));
    LL ans = 0;
    for(int i = 0;i <= n;i = nxt[i]){
        S.clear();
        int ps = i+1;
        if(a[ps] == a[i]) ps = nxt[ps];
        for(int j = ps;j <= n;j = nxt[j]){
            S[inv[j]]++;
        }
        for(int j = i+1;j <= n;j = nxt[j]){
            if(a[j] != a[i]) S[inv[j]]--;
            int t = 1ll*a[i]%ha*a[j]%ha;
            if(a[j] != a[i] && a[j] == a[j+1] && 1ll*t*a[j]%ha == 1) ans++;
//            t = qpow(t);
            ans += S[t];
        }
    }
    int cnt = 1;
    FOR(i,1,n){
        if(a[i] != a[i-1]){
            if(cnt >= 3) if(1ll*a[i-1]%ha*a[i-1]%ha*a[i-1]%ha == 1) ans++;
            cnt = 1;
        }
        else{
            cnt++;
        }
    }
    if(cnt >= 3) if(1ll*a[n]%ha*a[n]%ha*a[n]%ha == 1) ans++;
    //for(std::map<int,int>::iterator it = p.begin();it != p.end();++it){
    //    if(it->se < 3) continue;
    //    if(1ll*it->fi%ha*it->fi%ha*it->fi%ha == 1) ans++;
   // }
    printf("%lld\n",ans);
    return 0;
}
