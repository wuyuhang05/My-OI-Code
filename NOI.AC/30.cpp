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
const int MAXN = 1e5 + 5;
int n,a[MAXN],w,b[MAXN];

signed main(){
    scanf("%lld%lld",&n,&w);
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,1,n) scanf("%lld",b+i);
    std::reverse(a+1,a+n+1);std::reverse(b+1,b+n+1);
    int p=1,q=1,s1=0,s2=0,c=0,ans=0;
    while(p <= n && q <= n){
        if(s1 >= s2){
            while(s1 >= s2 && q <= n) c += w,s2 += b[q++],ans = std::max(ans,std::min(s1,s2)-c);
        }
        else{
            while(s2 >= s1 && p <= n) c += w,s1 += a[p++],ans = std::max(ans,std::min(s1,s2)-c);
        }
    }
    printf("%lld\n",ans);
    return 0;
}