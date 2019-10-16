/*
 * Author: RainAir
 * Time: 2019-08-31 11:36:36
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
#define P std::pair<char,char>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
const double EPS = 1e-3;
char str[MAXN];
int a[MAXN],b[MAXN],val[MAXN];
std::map<P,int> S;
int n,N;

struct Edge{
    int to;double w;int nxt;
}e[MAXN<<1];

int head[MAXN],cnt;

inline void add(int u,int v,double w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
//    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

inline int calc(P a){
    if(!S[a]) return S[a] = ++N;
    return S[a];
}

int du[MAXN],dis[MAXN];
bool inq[MAXN];

inline bool spfa(){
    FOR(i,1,N) du[i] = 0,dis[i] = 0,inq[i] = false;
    std::stack<int> q;
    FOR(i,1,N) q.push(i),inq[i] = true;
    while(!q.empty()){
        int v = q.top();q.pop();
        inq[v] = false;
        for(int i = head[v];i;i = e[i].nxt){
            DEBUG(dis[e[i].to]);DEBUG(dis[v]+e[i].w);
            if(dis[e[i].to] < dis[v]+e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                if(inq[e[i].to]) continue;
                inq[e[i].to] = true;
                q.push(e[i].to);
                du[e[i].to]++;
                if(du[e[i].to] > N) return true;
            }
        }
    }
    return false;
}

inline bool chk(double k){
    FOR(i,1,cnt) e[i].w -= k;
    bool res = spfa();
    FOR(i,1,cnt) e[i].w += k;
    return res;
}

inline void Solve(){
    double l = 0,r = 1e3,ans = -1;
    DEBUG(chk(21.46));return;
    while(r-l > EPS){
        double mid = (l + r) / 2.0;
        if(chk(mid)) ans = l = mid;
        else r = mid;
    }
    if(ans == -1) puts("No solution.");
    else printf("%.2f\n",r);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%s",str+1);
        int len = strlen(str+1);
        a[i] = calc(MP(str[1],str[2]));
        b[i] = calc(MP(str[len-1],str[len]));
        add(a[i],b[i],len);
    }   
    Solve();
    return 0;
}
