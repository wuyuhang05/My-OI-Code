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

const int MAXN = 3e5 + 5;
std::set<int> S[MAXN];
int a[MAXN];
int n;
std::vector<int> G[MAXN];

inline int gcd(int a,int b){
    return !b ? a : gcd(b,a%b);
}

inline void dfs(int v,int fa,int val){
    for(auto x:S[fa]) S[v].insert(gcd(x,a[v]));
    S[v].insert(val);
    val = gcd(val,a[v]);
    S[v].insert(val);
    for(auto x:G[v])
        if(x != fa) dfs(x,v,val);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    dfs(1,0,0);
    FOR(i,1,n) printf("%d ",*S[i].rbegin());
    return 0;
}

