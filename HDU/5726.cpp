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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
int a[MAXN],n;
int st[20][MAXN],Log[MAXN];

inline int gcd(int a,int b){
    return !b ? a : gcd(b,a%b);
}

inline void pre(){
    FOR(i,1,Log[n]){
        FOR(j,1,n){
            if(j+(1<<(i-1)) <= n) st[i][j] = gcd(st[i-1][j],st[i-1][j+(1<<(i-1))]);
        }
    }
}

inline int calc(int l,int r){
    int c = Log[r-l+1];
    return gcd(st[c][l],st[c][r-(1<<c)+1]);
}

std::map<int,LL> S;

inline void Solve(){
    scanf("%d",&n);CLR(st,0);
    FOR(i,1,n) scanf("%d",&a[i]),st[0][i] = a[i];
    pre();S.clear();
    FOR(i,1,n){
        int g = st[0][i],p = i;
        while(p <= n){
            int l = p,r = n,ans = p;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(calc(l,r) == g) ans = mid,l = mid+1;
                else r = mid-1;
            }
            S[g] += ans-p+1;p = ans+1;
            g = calc(i,p);
        }
    }
    int q;scanf("%d",&q);
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        int g = calc(l,r);
        printf("%d %lld\n",g,S[g]);
    }
}

int main(){
    Log[0] = -1;FOR(i,1,MAXN-5) Log[i] = Log[i>>1] + 1;
    int T;scanf("%d",&T);
    FOR(i,1,T) printf("Case #%d:\n",i),Solve();
    return 0;
}
