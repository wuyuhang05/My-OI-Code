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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int ha = 1e9 + 7;
const int MAXN = 1e5 + 5;

std::vector<int> a[MAXN];
int fac[MAXN],inv[MAXN];
int n;
int ans = 0;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline void prework(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

P st[MAXN];

inline int work(std::vector<int> x){
    int t = 0,res = 0;
    FOR(i,0,(int)x.size()-1){
        st[++t] = MP(i+1,x[i]);
        FOR(j,1,t) st[j].se = std::__gcd(st[j].se,x[i]);
        int _t = t;t = 0;
        FOR(j,1,_t) if(st[j].se == st[t].se) st[t].fi = st[j].fi;
        else st[++t] = st[j];
        FOR(j,1,t) (res += 1ll*(st[j].fi-st[j-1].fi)*st[j].se%ha) %= ha;
    }
    return res;
}

inline void add(int &x,int y){
    (x += y);if(x >= ha) x -= ha;
}

int pre[MAXN],suf[MAXN];// 单纯的前后缀数量
int all[MAXN],allm[MAXN],allm2[MAXN];// 个数 长度和 长度平方和
int ps[MAXN];// pre X suf 
int f[MAXN];

int main(){
    prework();scanf("%d",&n);int m = 0;
    FOR(i,1,n){
        int k;scanf("%d",&k);a[i].resize(k);
        FOR(j,0,k-1) scanf("%d",&a[i][j]),m = std::max(m,a[i][j]);
    }
    FOR(i,1,n) (ans += work(a[i])) %= ha;
    ans = 1ll*ans*fac[n]%ha;
    FOR(i,1,n){
        int m = a[i].size();
        int g = 0;
        std::vector<P> p,s;
        FOR(j,0,m-1){
            int _g = g;
            g = std::__gcd(g,a[i][j]);add(pre[g],1);
            if(g != _g) p.pb(MP(j+1,g));
        }
        g = 0;
        ROF(j,m-1,0){
            int _g = g;
            g = std::__gcd(g,a[i][j]);add(suf[g],1);
            if(g != _g) s.pb(MP(j+1,g));
        }
        p.pb(MP(m+1,0));s.pb(MP(0,0));
        FOR(i,0,(int)p.size()-2){
            FOR(j,0,(int)s.size()-2){
                int k = std::__gcd(p[i].se,s[j].se);
//                DEBUG(p[i+1].fi-p[i].fi);DEBUG(s[j].fi-s[j+1].fi);DEBUG(k);
                add(ps[k],1ll*(p[i+1].fi-p[i].fi)*(s[j].fi-s[j+1].fi)%ha);
            }
        }
        add(all[g],1);add(allm[g],m);add(allm2[g],1ll*m*m%ha);
    }
    FOR(i,1,1e5){
        for(int j = i*2;j <= 1e5;j += i){
            add(pre[i],pre[j]);add(suf[i],suf[j]);add(all[i],all[j]);add(allm[i],allm[j]);
            add(allm2[i],allm2[j]);add(ps[i],ps[j]);
        }
    }
    FOR(i,1,1e5){
        add(suf[i],ha-allm[i]);
        add(pre[i],ha-allm[i]);
  //      if(i == 1) DEBUG(ps[1]);
        add(ps[i],ha-allm2[i]);
    //    if(i == 1) DEBUG(ps[1]);
        FOR(j,0,all[i]-1){// suf + all + all / all + all + pre
            int t = 1ll*(pre[i]+suf[i])%ha*C(all[i]-1,j)%ha*allm[i]%ha*fac[j]%ha*fac[n-j-1]%ha;
            add(f[i],t);
        }
      //  if(i == 1) DEBUG(f[1]);
        FOR(j,0,all[i]){ // suf + all + pre
            int t = 1ll*(1ll*pre[i]*suf[i]%ha+ha-ps[i])%ha*C(all[i],j)%ha*fac[j]%ha;
            if(n-j-1 >= 0) t = 1ll*t*fac[n-j-1]%ha;
            add(f[i],t);
        }
        FOR(j,0,all[i]-2){ // all + all + all
            int t = 1ll*(1ll*allm[i]*allm[i]%ha+ha-allm2[i])%ha*C(all[i]-2,j)%ha*fac[j]%ha*fac[n-j-1]%ha;
            add(f[i],t);
        }
    }
    ROF(i,1e5,1){
        for(int j = i+i;j <= 1e5;j += i){
            add(f[i],ha-f[j]);
        }
    }
    FOR(i,1,1e5) add(ans,1ll*f[i]*i%ha);
    printf("%d\n",ans);
    return 0;
}
