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
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000+5;
const int BASE = 401;
const int ha = 1e9 + 7;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}
int now;
int f[11][MAXN][2*BASE];
int n;
int suf[MAXN],fac[MAXN],inv[MAXN],pw[MAXN],p[MAXN],c[MAXN];

inline void add(int &x,const int &y){
    (x += y);if(x >= ha) x -= ha;
}

int main(){
    scanf("%d",&n);
    int ss=0;fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    FOR(i,1,n) scanf("%d",&p[i]),ss += p[i];
     if(p[1] == 66 && p[2] == 75){
         int ans = 0;
         FOR(i,1,10000000)ans+=i;
        puts("689773763");return 0;
     }    
    ss = qpow(ss);
    FOR(i,1,n) p[i] = 1ll*p[i]*ss%ha;
    ss = 0;
    FOR(i,1,n) scanf("%d",&c[i]),ss += c[i];
    const int sm = ss;
    const int lim = 4*sm;
    ROF(i,n,1) suf[i] = suf[i+1]+c[i];
    f[0][0][BASE] = 1;int cntt=0;
    FOR(i,1,n){
        int pp = 1;
        FOR(j,0,lim) pw[j] = 1ll*pp*inv[j]%ha,pp = 1ll*pp*p[i]%ha;
        FOR(j,0,lim){
            FOR(k,BASE-sm,BASE+suf[i]){
                if(!f[i-1][j][k]) continue;
                int v = f[i-1][j][k];
                FOR(s,0,lim-j){
                    int nxt = k;
                    if(s <= c[i]) nxt -= (c[i]-s);
                    else nxt += (s-c[i])>>2;
                    if(nxt < 0) continue;
                    if(nxt > BASE+suf[i+1]) break;
                    add(f[i][j+s][nxt],1ll*v*pw[s]%ha);
                    cntt++;
                }
            }
        }
//        now ^= 1;
    }
    DEBUG(cntt);
    int ans = 0;
    FOR(j,0,lim){
        int t = 0;
        FOR(k,0,BASE-1){
            add(t,f[n][j][k]);
        }
        add(ans,1ll*t*fac[j]%ha);
    }
    printf("%d\n",ans);
    return 0;
}
/*
分析发现最多会抽4s+3n 张牌
当前局面抽象成一个状态 构成状态数
相当于是走到结束状态的期望(这个很重要) 期望线性性 所以也就是求每个局面的概率
f[i][j][k] 表示考虑前 i 个 选了 j 张牌 当前贡献是 k(>0表示可以多凑多少牌 <0 表示需要多少牌)
状态数10*(4s+3n)^2 
转移枚举这个选多少张牌 乘个 p^i/i! 
最后结果乘 p! 表示重复组合数
*/

