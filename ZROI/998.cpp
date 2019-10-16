/*
 * Author: RainAir
 * Time: 2019-09-08 14:53:49
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

const int MAXN = 1000+5;

struct Node{
    int l,r,w,s,v;

    bool operator < (const Node &t) const {
        return r == t.r ? l > t.l : r < t.r;
    }
}a[MAXN];
int f[MAXN][MAXN],g[MAXN][MAXN];
int n,S;

int main(){
    scanf("%d%d",&n,&S);
    FOR(i,1,n) scanf("%d%d%d%d%d",&a[i].l,&a[i].r,&a[i].w,&a[i].s,&a[i].v);
    a[n+1] = (Node){0,2*n+1,0,S,0};++n;
    std::sort(a+1,a+n+1);
    FOR(i,1,n){
        int t = std::min(a[i].s,S-a[i].w),j = 1;
        CLR(g,0);
        while(a[j].r <= a[i].l && j <= n) ++j;
        if(j > n) continue;
        FOR(k,a[i].l+1,a[i].r){
            memcpy(g[k],g[k-1],sizeof(g[k]));
            for(;j < i && a[j].r == k;++j){
                if(a[j].l < a[i].l) continue; // 可以取到等号
                FOR(l,0,t) g[a[j].r][l] = std::max(g[a[j].r][l],g[a[j].l][l]+f[j][l]);
            }
        }
        FOR(l,0,t) f[i][l+a[i].w] = g[a[i].r][l] + a[i].v;
        FOR(l,1,t) f[i][l] = std::max(f[i][l],f[i][l-1]);
    }
    printf("%d\n",f[n][S]);
    return 0;
}
