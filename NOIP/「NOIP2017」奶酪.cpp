#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << (x) << std::endl
#define pow(x) 1.0*(x)*(x)
#define int long long
const int MAXN = 1000 + 5;

struct Point{
    int x,y,z;
    
    double operator + (const Point &other) const {
        return std::sqrt(pow(x-other.x)+pow(y-other.y)+pow(z-other.z));
    }
}p[MAXN];

int N,H,R;
int f[MAXN];

int find(int x){
    int r = x;
    while(f[r] != r) r = f[r];
    int k = x;
    while(k != r){
        int t = f[k];
        f[k] = r;
        k = t;
    }
    return r;
}

inline void Union(int x,int y){
    int fx = find(x),fy = find(y);
    f[fx] = fy;
}

inline void build(){
    FOR(i,1,N+2) f[i] = i;
    FOR(i,1,N){
        if(p[i].z-R <= 0) Union(N+1,i);
        if(p[i].z+R >= H) Union(N+2,i);
    }
    FOR(i,1,N){
        FOR(j,i+1,N){
            // DEBUG(p[i]+p[j]);
            if(p[i] + p[j] <= 1.0*2*R) Union(i,j);
        }
    }
}

inline void Solve(){
    scanf("%lld%lld%lld",&N,&H,&R);
    FOR(i,1,N) scanf("%lld%lld%lld",&p[i].x,&p[i].y,&p[i].z);
    build();
    if(find(N+1) == find(N+2)) puts("Yes");
    else puts("No");
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}
