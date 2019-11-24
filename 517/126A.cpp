/*
 * Time: 2019-11-12 11:25:47
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 6e5 + 5;
int a[MAXN],n;
int sm[MAXN];
int p[MAXN];

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",a+i),p[a[i]]++;
    std::sort(p+1,p+n+1);std::reverse(p+1,p+n+1);
    int sz = 1;while(p[sz]) ++sz;sz--;
    std::sort(p+1,p+sz+1);
    int tp = 1,now = 0;
    FOR(k,1,n){
        while(tp <= sz && p[tp] < k) now += p[tp++];
        sm[k] = k*(sz-tp+1)+now;
    }
    FOR(k,1,n){
        int l = 0,r = n,ans = 0;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(sm[mid] >= k*mid) ans = mid,l = mid+1;
            else r = mid-1;
        }
        printf("%lld ",ans);
    }
    puts("");
    return 0;
}
