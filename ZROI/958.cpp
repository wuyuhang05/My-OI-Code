/*
 * Author: RainAir
 * Time: 2019-09-08 16:07:38
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

const int MAXN = 2e5 + 5;

int f[2][MAXN],dis[2][MAXN],nxt[2][MAXN],n;
std::queue<int> q;
bool vis[2][MAXN];

inline int find(int o,int x){
    if(f[o][x] == x) return x;
    int v = find(o,f[o][x]);
    dis[o][x] += dis[o][f[o][x]];
    return f[o][x] = v;
}

inline void add(int o,int x){
    if(vis[o][x]) return;
    vis[o][x] = true;
    q.push((x<<1) | o);
}

inline bool chk(int k){
    FOR(i,1,n) f[0][i] = f[1][i] = i,dis[0][i] = dis[1][i] = vis[0][i] = vis[1][i] = 0;
    while(!q.empty()) q.pop();
    add(0,1);add(1,1);
    while(!q.empty()){
        int v = q.front();q.pop();
        int o = v&1,rem = k-1;
        v = nxt[o][v>>1];
        bool flag = false;
        while(true){
            int t = find(o,v); // pushup
            if(rem < dis[o][v]) break;
            rem -= dis[o][v];v = t;
            add(o^1,v);
            if(find(o,nxt[o][v]) != v){
                f[o][v] = nxt[o][v];
                dis[o][v] = 1;
                continue;
            }
            if(flag || !rem) break;
            flag = true; // 环只走一次
            rem--;
            v = nxt[o][v];
            add(o^1,v);
        }
    }
    return vis[0][n] || vis[1][n];
}

int main(){
    scanf("%d",&n);
    if(n == 1){
        puts("0");
        return 0;
        //fuck
    }
    FOR(i,1,n) scanf("%d%d",nxt[0]+i,nxt[1]+i);
    int l = 1,r = n,ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) r = mid - 1,ans = mid;
        else l = mid + 1;
    }
    printf("%d\n",ans);
    return 0;
}
