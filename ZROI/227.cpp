/*
 * Author: RainAir
 * Time: 2019-09-14 11:54:34
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
const int MAXM = (1<<20)+3;

int dis[MAXM];
int n,m;
int a[MAXN];
char str[MAXN];

inline void bfs(){
    FOR(i,0,(1<<m)-1) dis[i] = 1e9;
    FOR(i,1,n) dis[a[i]] = 0;
    std::queue<int> q;
    FOR(i,1,n) q.push(a[i]);
    while(!q.empty()){
        int v = q.front();q.pop();
        FOR(i,1,m){
            int to = v^(1<<(i-1));
            if(dis[to] > dis[v] + 1){
                dis[to] = dis[v] + 1;
                q.push(to);
            }
        }
    }
    int ans = 0,mx = 0;
    FOR(i,0,(1<<m)-1) mx = std::max(mx,dis[i]);//,DEBUG(dis[i]);
    FOR(i,0,(1<<m)-1) if(dis[i] == mx) ans++;
    printf("%d %d\n",m-mx,ans);
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n-1){
        scanf("%s",str+1);
        int x = 0;
        FOR(i,1,m) x = (x<<1)|(str[i]-'0');
        a[i] = x;
    }
    std::sort(a+1,a+n);
    n = std::unique(a+1,a+n) - a - 1;
    bfs();
    return 0;
}
