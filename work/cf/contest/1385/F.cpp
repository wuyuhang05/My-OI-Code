#include <algorithm>
#include <cassert>
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

const int MAXN = 2e5 + 5;

int n,k;
int du[MAXN];
std::set<P> S;
std::set<int> GG[MAXN],G[MAXN];

inline void Solve(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n) du[i] = 0,G[i].clear(),GG[i].clear();S.clear();
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        du[u]++;du[v]++;GG[u].insert(v);GG[v].insert(u);
    }
    FOR(i,1,n){
        if(du[i] == 1){
            G[*GG[i].begin()].insert(i);
        }
    }
    FOR(i,1,n) S.insert(MP(G[i].size(),i));
    int ans = 0;
    while(true){
        if(S.empty()) break;
        if((*S.rbegin()).fi < k) break;
        int v = (*S.rbegin()).se;
        S.erase(MP(G[v].size(),v));
        ++ans;
        FOR(i,1,k){
            GG[v].erase(*G[v].begin());
            G[v].erase(G[v].begin());
        }
//        DEBUG(v);
        if(G[v].empty()){
            if(GG[v].empty()) break;
            if(GG[v].size() != 1){
                S.insert(MP(G[v].size(),0));
                continue;
            }
            int t = *GG[v].begin();GG[v].clear();
            S.erase(MP(G[t].size(),t));
            G[t].insert(v);
            S.insert(MP(G[t].size(),t));
        }
        else{
            S.insert(MP(G[v].size(),v));
        }
    }
    printf("%d\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
