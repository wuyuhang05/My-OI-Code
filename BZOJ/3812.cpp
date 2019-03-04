#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 15 + 5;
const int ha = 1e9 + 7;

int head[MAXN],cnt;
int eout[MAXN],ein[MAXN],pw[MAXN],cnt[MAXN];
int f[MAXN],g[MAXN],h[MAXN],p[MAXN];

int n,m;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        u = (1<<u)-1;v = (1<<v)-1;
        eout[u] |= v;ein[v] |= u;
    }
    pw[0] = 1;
    FOR(i,1,MAXN-1) pw[i] = (pw[i-1]<<1)%ha;
    cnt[0] = 0;
    FOR(i,1,MAXN-1) cnt[i] = cnt[i-(i&-i)]+1;
    FOR(S,1,(1<<n)-1){
        int one = S&-S,out = S^one;
        for(int i = out;i;i = (i-1)&out){
            g[S] = (g[S]-f[S^i]*g[i]%ha+ha)%ha;
        }
        h[S] = h[out]+cnt[ein[one]&out] + cnt[eout[one]&out];
        f[S] = pw[h[S]];
        for(int i = S;i;i=(i-1)&S){
            if(i != S){
                int one = (i^S)&-(i^S);

            }
            else p[i] = 0;
        }
    }
    return 0;
}