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

int ans = 0;
int a[12];

inline int lcm(int x,int y){
    return x*y/std::__gcd(x,y);
}

inline void upd(int n){
    std::set<int> _;_.insert(1);
    FOR(S,1,(1<<n)-1){
        int t = 1;
        FOR(i,0,n-1){
            if((S>>i)&1) t = lcm(t,a[i+1]);
        }
        _.insert(t);
    }
    ans = std::max(ans,(int)_.size());
}

inline void dfs(int n,int step){
    if(!n){
        DEBUG(step)
        upd(step);return;
    }
    if(a[step-1] > n) return;
    FOR(i,a[step-1],n) a[step] = i,dfs(n-i,step+1);
}

int main(){
    int n;a[0] = 1;
    scanf("%d",&n);
    dfs(n,1);
    printf("%d\n",ans);
    return 0;
}
