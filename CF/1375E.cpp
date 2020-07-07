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

const int MAXN = 1000+5;
int a[MAXN],n,id[MAXN],b[MAXN];
std::vector<int> S;
std::vector<P> ans;

inline bool cmp(int x,int y){
    if(a[x] != a[y]) return a[x] < a[y];
    return x < y;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),S.pb(a[i]),id[i] = i,b[i] = a[i];
    std::sort(id+1,id+n+1,cmp);
    ROF(i,n,1){
        int ps = i;
        while(ps+1 <= n && id[ps] > id[ps+1]){
            ans.pb(MP(id[ps],id[ps+1]));
            std::swap(id[ps],id[ps+1]);
            ps++;
        }
    }
    printf("%d\n",(int)ans.size());
    for(auto x:ans) printf("%d %d\n",std::min(x.fi,x.se),std::max(x.fi,x.se));
    for(auto x:ans) std::swap(b[x.fi],b[x.se]);
//    FOR(i,1,n) printf("%d ",b[i]);puts("");
    return 0;
}
