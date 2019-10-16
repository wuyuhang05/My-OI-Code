/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-13 19:38:40
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

const int MAXN = 5000+5;
const int ha = 998244353;
int n,m;
int a[MAXN],b[MAXN];
int F[MAXN][MAXN],G[MAXN][MAXN];//  长度为 i 以 j 结尾
int f[MAXN][MAXN],g[MAXN][MAXN],h[MAXN][MAXN]; // A 串 i 结尾 b 串 j 结尾 长度相同
// f:> g:= h:<
int prea[MAXN],preb[MAXN];
int ps[MAXN],ans = 0;

inline int calcf(int a,int b,int c,int d){
    int res = f[c][d];
    if(a) res = (res+ha-f[a-1][d]) % ha;
    if(b) res = (res+ha-f[c][b-1]) % ha;
    if(a && b) (res += f[a-1][b-1]) %= ha;
    return res;
}

inline int calcg(int a,int b,int c,int d){
    int res = g[c][d];
    if(a) res = (res+ha-g[a-1][d]) % ha;
    if(b) res = (res+ha-g[c][b-1]) % ha;
    if(a && b) (res += g[a-1][b-1]) %= ha;
    return res;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i),prea[i] = ps[a[i]],ps[a[i]] = i;
    FOR(i,1,n) ps[i] = 0;
    FOR(i,1,m) scanf("%d",b+i),preb[i] = ps[b[i]],ps[b[i]] = i;
    FOR(i,0,n) F[0][i] = 1;
    FOR(i,1,n){
        FOR(j,1,n){
            if(!prea[j]) F[i][j] = F[i-1][j-1];
            else F[i][j] = (F[i-1][j-1] - F[i-1][prea[j]-1] + ha)%ha;
        }
        FOR(j,1,n) (F[i][j] += F[i][j-1]) %= ha;
    }
    FOR(i,0,m) G[0][i] = 1;int smG = 0;
    FOR(i,1,m){
        FOR(j,1,m){
            if(!preb[j]) G[i][j] = G[i-1][j-1];
            else G[i][j] = (G[i-1][j-1] - G[i-1][preb[j]-1] + ha)%ha;
        }
        FOR(j,1,m) (G[i][j] += G[i][j-1]) %= ha;
    }
    FOR(i,1,n) (smG += G[i][m]) %= ha;
    ROF(i,n,2){
        smG = (smG - G[i][m] + ha) % ha;
        (ans += 1ll*smG*F[i][n]%ha) %= ha;
    }
    FOR(i,0,n) g[i][0] = 1;
    FOR(i,0,m) g[0][i] = 1;
    FOR(i,1,n){
        FOR(j,1,m){
            f[i][j] = ((f[i-1][j]+f[i][j-1])%ha - f[i-1][j-1] + ha) % ha;
            g[i][j] = ((g[i-1][j]+g[i][j-1])%ha - g[i-1][j-1] + ha) % ha;
            if(a[i] == b[j]) (g[i][j] += calcg(prea[i],preb[j],i-1,j-1)) %= ha;
            if(a[i] > b[j]) (f[i][j] += calcg(prea[i],preb[j],i-1,j-1)) %= ha;
            (f[i][j] += calcf(prea[i],preb[j],i-1,j-1)) %= ha;
        }
    }
    (ans += f[n][m])%=ha;
    printf("%d\n",ans);
    return 0;
}
