/*
 * Author: RainAir
 * Time: 2019-09-05 18:25:38
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 300+5;
const P e = MP(0,0);
//#define deb (up == 1 && down == 2)
#define deb (1+1 == 3)
int a[MAXN][MAXN],n,m,k;
int sm[MAXN][MAXN],t[MAXN];
P st[MAXN];
int top;

signed main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    FOR(i,1,n) FOR(j,1,m) scanf("%lld",&a[i][j]),a[i][j] -= k;
    FOR(i,1,n) FOR(j,1,m) sm[i][j] += sm[i-1][j] + a[i][j];
    int ans = 0;
    FOR(up,1,n){
        FOR(down,up,n){
            FOR(i,1,m) t[i] = sm[down][i]-sm[up-1][i],t[i] += t[i-1];
            if(deb) FOR(i,1,m) DEBUG(t[i]);
            FOR(i,0,top) st[i] = e;
            top = 0;
            FOR(i,0,m){
                if(deb) DEBUG(top);
                if(top > 0){
                    int l = 1,r = top,res = -1;
                    while(l <= r){
                        int mid = (l + r) >> 1;
                        if(st[mid].fi <= t[i]) res = mid,r = mid - 1;
                        else l = mid+1;
                    }
                    if(res != -1) ans = std::max(ans,(i-st[res].se)*(down-up+1));
                }
                if(t[i] < st[top].fi || top == 0) st[++top] = MP(t[i],i);
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
