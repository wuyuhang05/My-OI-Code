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

const int MAXN = 2e5 + 10;
int a[MAXN<<1],b[MAXN<<1],n,t;

int main(){
    scanf("%d",&n);
    FOR(i,0,n-1) scanf("%d",b+i);
    FOR(i,1,n){
        scanf("%d",a+i);if(a[i] == 1)t = i;
    }
    int ans = 0,res = 0;
    std::multiset<int> p;
    FOR(i,0,n-1) if(b[i]) p.insert(b[i]);
    int now = 1;
    while(!p.empty() && ans < n){
        a[n+now] = *p.begin();p.erase(p.begin());
        if(a[now]) p.insert(a[now]);now++;ans++;
    }
    FOR(i,1,n) if(a[now+i-1] != i) ans = INT_MAX;
    res = ans;ans = 0;
    FOR(i,t+1,n) if(a[i] != 0) ans = std::max(ans,i-t-a[i]+1);
    ans += t+n;
    printf("%d\n",std::min(res,ans));
    return 0;
}
