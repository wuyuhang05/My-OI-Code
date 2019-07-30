/*
 * Author: RainAir
 * Time: 2019-07-23 18:34:09
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
#define P std::pair<int,int>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3e5 + 5;
int n,m,cnt;
P seg[MAXN];
int f[21][MAXN],a[MAXN],b[MAXN];
int mn[MAXN];

int main(){
    scanf("%d%d",&m,&n);
    FOR(i,1,n){
        int l,r;scanf("%d%d",&l,&r);
        if(l < r) seg[++cnt] = MP(l,r),seg[++cnt] = MP(l+m,r+m);
        else seg[++cnt] = MP(l,r+m);
    }
    std::sort(seg+1,seg+cnt+1);
    FOR(i,1,cnt) a[i] = seg[i].fi,b[i] = seg[i].se;
    mn[cnt] = cnt;
    ROF(i,cnt-1,1) mn[i] = seg[i].se < seg[mn[i+1]].se ? i : mn[i+1];
    FOR(i,1,cnt){
        int p = 0;
        if(i+1 <= cnt) p = std::lower_bound(a+i+1,a+cnt+1,seg[i].se)-a;
        f[0][i] = mn[p];
    }
    int ans = 0;
    FOR(i,1,20) FOR(j,1,cnt) f[i][j] = f[i-1][f[i-1][j]];
    FOR(i,1,cnt){
        int R = i,res = 1;
        ROF(j,20,0) {
            if(f[j][R] && seg[f[j][R]].se <= seg[i].fi+m) R = f[j][R],res += (1<<j);
        }
        ans = std::max(ans,res);
    }
    printf("%d\n",ans);
    return 0;
}
