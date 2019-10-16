/*
 * Author: RainAir
 * Time: 2019-10-13 13:42:33
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
#define P std::pair<LL,LL>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 2e5 + 5;
const int MAXM = 1000 + 5;
int a[MAXN];
int S[MAXN];
int s[MAXM],c[MAXM],t[MAXM][MAXM];
int n,m;

std::priority_queue<P,std::vector<P>,std::greater<P> > q;

inline LL chk(int k){
    int ans = 0;
    FOR(i,1,1000) ans += c[i]*(k/i) - s[i] - t[i][k%i+1];
    return ans;
}

signed main(){
//    freopen("c.in","r",stdin);
//    freopen("c.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n) scanf("%lld",a+i),++c[a[i]];
    FOR(i,1,n){
        if(i != 1){
            P v = q.top();q.pop();
            S[i] = v.fi;v.fi += v.se;
            q.push(v);
        }
        else S[i] = 0;
        q.push(MP(S[i]+a[i],a[i]));
    }
    FOR(i,1,n) s[a[i]] += S[i]/a[i],t[a[i]][S[i]%a[i]]++;
    FOR(i,0,1000) ROF(j,i,0) t[i][j] += t[i][j+1];
    FOR(i,1,m){
        int x;scanf("%lld",&x);
        if(x <= n-1){
            printf("%lld ",S[x+1]);continue;
        }
        int l = 0,r = 1e12,ans = 0;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(chk(mid) >= x) ans = mid,r = mid-1;
            else l = mid+1;
        }
        printf("%lld ",ans);
    }
    puts("");
    return 0;
}


