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

const int MAXN = 2e5 + 5;

std::vector<int> G[MAXN];
int u[MAXN],v[MAXN],w[MAXN];
int n,m;
int du[MAXN],dis[MAXN];

inline void Solve(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) G[i].clear(),du[i] = dis[i] = 0;
    FOR(i,1,m){
        scanf("%d%d%d",w+i,u+i,v+i);
        if(w[i]) G[u[i]].pb(v[i]),du[v[i]]++;
    }
    std::queue<int> q;
    FOR(i,1,n) if(!du[i]) q.push(i);
    int ts=0;
    while(!q.empty()){
        int v = q.front();q.pop();dis[v] = ++ts;
        for(auto x:G[v]){
            if(!--du[x]){
                q.push(x);
            }
        }
    }
    if(ts != n){
        puts("NO");
        return;
    }
    puts("YES");
    FOR(i,1,m){
        if(w[i]) printf("%d %d\n",u[i],v[i]);
        else{
            if(dis[u[i]] > dis[v[i]]) std::swap(u[i],v[i]);
            printf("%d %d\n",u[i],v[i]);
        }
    }
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
