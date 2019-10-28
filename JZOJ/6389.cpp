/*
 * Author: RainAir
 * Time: 2019-10-26 21:22:00
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
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
const int ha = 998244353;
std::set<int> S[MAXN];
int f[MAXN];
int n,m;

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline void merge(int x,int y){
    x = find(x),y = find(y);
    if(S[x].size() < S[y].size()) std::swap(x,y);
    f[y] = x;
    for(auto xx:S[y]) S[x].insert(xx);
    S[y].clear();
}

int main(){
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    scanf("%d%d",&n,&m);
    FOR(i,1,n) f[i] = i;
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        if(u > v) std::swap(u,v);
        S[u].insert(v);
    }
    int ans = 1;
    FOR(i,1,n){
        while(!S[find(i)].empty() && (*S[find(i)].begin()) <= i) S[find(i)].erase(S[find(i)].begin());
        ans = 1ll*ans*(n-(int)S[find(i)].size())%ha;
        if(!S[find(i)].empty()){
            merge(i,(*S[find(i)].begin()));
        }
    }
    printf("%d\n",ans);
    return 0;
}
