/*
 * Author: RainAir
 * Time: 2019-08-18 19:01:38
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 300000+5;

int s[MAXN],fac[MAXN],b[MAXN],pw[MAXN],cnt[MAXN];
int ls[MAXN],ln,n,m,ans[MAXN];
std::vector<std::pair<int,int> > dec;

struct BIT{
    int tree[MAXN];
    #define lowbit(x) ((x)&(-x))

    inline void clear(){
        CLR(tree,0);
    }
    
    inline void add(int pos,int x){
        while(pos <= n){
            tree[pos] += x;
            pos += lowbit(pos);
        }
    }

    inline int query(int pos){
        int res = 0;
        while(pos){
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
}bit;

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = res*a;
        a = a*a;n >>= 1;
    }
    return res;
}

inline void fg(int x){
    int q = std::sqrt(1.0*x);
    FOR(i,2,q){
        if(!(x%i)){
            int cnt = 0;
            while(!(x%i)) x /= i,cnt++;
            dec.pb(MP(i,cnt));
        }
    }
    if(x != 1) dec.pb(MP(x,1));
}

inline void exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1;y = 0;
        return;
    }
    exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
}

inline int inv(int a,int b){ // ax==1 (mod b)
    int x,y;exgcd(a,b,x,y);
    return (x+b)%b;
}

inline int solve(int p,int e){
    int P = qpow(p,e);bit.clear();
    fac[0] = 1;pw[0] = 1;b[0] = 0;
    FOR(i,1,n){
        int tot = 0,t = i;
        while(!(t%p)) t /= p,tot++;
        fac[i] = fac[i-1]*t%P;
        b[i] = b[i-1]+tot;
        pw[i] = pw[i-1]*p%P;
        bit.add(s[i],1);cnt[s[i]]++;
    }
    // FOR(i,1,n) DEBUG(cnt[i]);
    int ans = 0,invb = 0,inv = 1;
    FOR(i,1,ln) inv = 1ll*inv*::inv(fac[cnt[i]],P)%P,invb += b[cnt[i]];
    FOR(i,1,n){
        (ans += bit.query(s[i]-1)*fac[n-i]%P*inv%P*pw[b[n-i]-invb]%P) %= P;
        inv = 1ll*inv*fac[cnt[s[i]]]%P*::inv(fac[cnt[s[i]]-1],P)%P;
        invb -= b[cnt[s[i]]];invb += b[--cnt[s[i]]];
        bit.add(s[i],-1);
    }
 //   FOR(i,1,n) assert(!cnt[i]);
    ans++;ans %= P;
    return ans;
}

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n) scanf("%lld",s+i),ls[i] = s[i];
    std::sort(ls+1,ls+n+1);
    ln = std::unique(ls+1,ls+n+1)-ls-1;//DEBUG(ln);
    FOR(i,1,n) s[i] = std::lower_bound(ls+1,ls+ln+1,s[i])-ls;
    fg(m);
    int sz = dec.size(),res = 0;
    FOR(i,1,sz) ans[i] = solve(dec[i-1].fi,dec[i-1].se);
    FOR(i,1,sz){
        int P = qpow(dec[i-1].fi,dec[i-1].se);
        int inv = ::inv(m/P,P);
        (res += m/P*inv%m*ans[i]%m) %= m;
    }
    printf("%lld\n",(res+m)%m);
    return 0;
}
