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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200 + 5;
const int MAXM = 10;
#define lowbit(x) (x&-x)

int a[MAXN][MAXN],f[MAXN][(1<<MAXM)+1],cnt[MAXN],bit[MAXN],pc[MAXN],rt[2][MAXN];
int n,m,S;

inline bool chk(int S,int x){
    FOR(i,1,m-1){
        if((!a[x][i] || !a[x][i-1]) && !(S&bit[i])) return false;
    }
    return true;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,0,n-1) FOR(j,0,m-1) scanf("%d",&a[i][j]),cnt[i] += !a[i][j];
    S = (1<<m-1);
    FOR(i,1,m-1) bit[i] = 1<<i-1;
    pc[0] = 1;
    FOR(i,1,S-1) pc[i] = pc[i^lowbit(i)] + 1;CLR(f,0x3f);
    FOR(i,0,S-1) if(chk(i,0)) f[0][i] = pc[i]-cnt[0];
    FOR(i,0,n-1){
        FOR(j,0,S-1){
            if(!chk(j,i)) continue;
            FOR(k,0,S-1){
                if(!chk(k,i+1)) continue;
                int t = f[i][j] + pc[k] - cnt[i+1];
                rt[0][m-1] = m;
                ROF(l,m-2,0) rt[0][l] = (j&bit[l+1]) ? l+1 : rt[0][l+1];
                rt[1][m-1] = m;
                ROF(l,m-2,0) rt[1][l] = (k&bit[l+1]) ? l+1 : rt[1][l+1];
                FOR(l,0,m-1){
                    if(a[i][l] && a[i+1][l] && (l == 0 || (j&bit[l]) && (k& bit[l])) && rt[0][l] == rt[1][l]) t--;
                }
                f[i+1][k] = std::min(f[i+1][k],t);
            }
        }
    }
    int ans = INT_MAX;
    FOR(i,0,S-1) ans = std::min(ans,f[n-1][i]);
    printf("%d\n",ans);
    return 0;
}