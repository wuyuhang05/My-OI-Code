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

const int MAXN = 1000+5;
int n,m,q;
int a[MAXN][MAXN];
std::pair<int,P> b[MAXN];
P p[MAXN][MAXN];
int cnt[MAXN][MAXN];
int ans[MAXN];
int N;

int main(){
    scanf("%d%d%d",&n,&m,&q);
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&a[i][j]);
    FOR(i,1,n){
        FOR(j,1,m) b[j] = MP(a[i][j],MP(i,j));
        std::sort(b+1,b+m+1);std::reverse(b+1,b+m+1);
        FOR(j,1,m) p[b[j].se.fi][b[j].se.se].fi = j;
    }
    FOR(j,1,m){
        FOR(i,1,n) b[i] = MP(a[i][j],MP(i,j));
        std::sort(b+1,b+n+1);std::reverse(b+1,b+n+1);
        FOR(i,1,n) p[b[i].se.fi][b[i].se.se].se = i;
    }
    FOR(i,1,n) FOR(j,1,m) cnt[p[i][j].fi][p[i][j].se]++;
    FOR(i,1,q){
        int x,y;scanf("%d%d",&x,&y);
        printf("%d\n",cnt[x][y]);
    }
    return 0;
}