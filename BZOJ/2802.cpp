/*
 * Author: RainAir
 * Time: 2019-07-24 18:27:49
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
const int MAXN = 250000+5;
int n;
int a[MAXN],b[MAXN];
std::priority_queue<P> q;
std::vector<int> v;

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,1,n) scanf("%lld",b+i);
    int sum = 0,ans = 0;
    FOR(i,1,n){
        sum += a[i];
        if(sum >= b[i]) ++ans,sum -= b[i],q.push(MP(b[i],i));
        else if(!q.empty()){
            int t = q.top().fi;
            if(t > b[i]){
                q.pop();sum -= b[i];sum += t;
                q.push(MP(b[i],i));
            }
        }
    }
    printf("%lld\n",ans);
    while(!q.empty()) v.pb(q.top().se),q.pop();
    std::sort(all(v));
    FOR(i,0,(int)v.size()-1) printf("%lld ",v[i]);puts("");
    return 0;
}
