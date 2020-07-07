#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cassert>
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
#define db double
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

const int MAXN = 5e5 + 5;
int a[MAXN],p[MAXN],v[MAXN],n;
int id[MAXN];
std::vector<int> G[MAXN];

int ans = 0;

inline void work(){
    int now = 0;std::multiset<int> S;
    int sm = 0;
    FOR(i,1,n){
        for(auto x:G[id[i]]) S.insert(x);
        if(S.empty()) return;
        if((*S.rbegin()) < p[id[i]]) S.erase(S.begin());
        else S.erase(S.lower_bound(p[id[i]])),now++;
    }
    ans = std::max(ans,now);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n) scanf("%d",p+i);
    FOR(i,1,n) scanf("%d",v+i);
    FOR(i,1,n) G[a[i]].pb(v[i]);
    // 合法要求任意时刻 sum>=i 
    // 如果取 i+1 作为开头 那么 sum[j] = sm[j]-sm[i]
    // 取最小的一定有解
    int mn = 1e9,ps = -1,sm = 0;
    FOR(i,1,n){
        sm += (int)G[i].size()-1;
        if(mn > sm){
            mn = sm;
            ps = i;
        }
    }
    ps = ps%n+1;
    int tot = 0;
    FOR(i,1,n-ps+1) id[i] = ps+i-1;
    FOR(i,n-ps+2,n) id[i] = i-(n-ps+1);
    work();
    printf("%d\n",ans);
    return 0;
}
