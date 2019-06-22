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
#define int LL
const int MAXN = 1e5 + 5;
int a[MAXN],n,k;
bool vis[MAXN];
signed main(){
    scanf("%lld%lld",&n,&k);
    FOR(i,1,n) scanf("%lld",a+i);
    std::sort(a+1,a+n+1);int ans = n;
    FOR(i,1,n){
        if(!vis[i]){
            vis[i] = true;
            int t = a[i]*k;
            if(t > a[n]) continue;
            int l = i+1,r = n;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(a[mid] < t) l = mid+1;
                else if(a[mid] > t) r = mid-1;
                else{
                    vis[mid] = true;ans--;break;
                }
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
