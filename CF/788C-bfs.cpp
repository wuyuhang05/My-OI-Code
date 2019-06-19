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

const int MAXN = 1000;
std::vector<int> v;
int n,k;
bool vis[MAXN+5];
int dis[MAXN*2+5];

inline void bfs(){
    std::queue<int> q;
    FOR(i,0,MAXN){
        if(vis[i]){
            v.pb(i-n);
            dis[i-n+MAXN] = 1;
            if(i-n+MAXN == MAXN) return;
            q.push(i-n+MAXN);
        }
    }
    while(!q.empty()){
        for(auto delta:v){
            int x = q.front()+delta;
            if(x < 0 || x > 2000 || dis[x] <= dis[q.front()]+1) continue;
            dis[x] = dis[q.front()]+1;
            if(x == MAXN) return;
            q.push(x);
        }
        q.pop();
    }
}

int main(){
    scanf("%d%d",&n,&k);CLR(dis,0x3f);
    FOR(i,1,k){
        int x;scanf("%d",&x);
        vis[x] = true;
    }
    bfs();
    printf("%d\n",dis[MAXN] == 0x3f3f3f3f ? -1 : dis[MAXN]);
    return 0;
}
