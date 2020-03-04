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

const int MAXN = 3000 + 5;
const int ha = 998244353;
std::map<std::vector<int>,int> mp;
int tot;
int nxt[MAXN][5];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    for(;n;a = 1ll*a*a%ha,n>>=1) if(n&1) res = 1ll*res*a%ha;
    return res;
}

inline void chkmax(int &a,int b){
    if(a < b) a = b;
}

inline void add(int &a,int b){
    (a += b);if(a >= ha) a -= ha;
}
inline int dfs(std::vector<int> now){
    if(mp.count(now)) return mp[now];
    mp[now] = ++tot;int id = tot;
    FOR(i,0,4){
        std::vector<int> nxt(19,-1);
        nxt[18] = now[18]+(i>=2);
        FOR(a,0,2){ // i-2 i-1 i
            FOR(b,0,2){ // i-1 i i+1
                FOR(c,0,2){ // i i+1 i+2
                    if(a+b+c > i) break;
                    if(now[a+3*b] != -1) chkmax(nxt[b+3*c],now[a+3*b]+a+(i-a-b-c)/3);
                    if(now[a+3*b+9] != -1) chkmax(nxt[b+3*c+9],now[a+3*b+9]+a+(i-a-b-c)/3);
                    if(a+b+c+2 <= i && now[a+3*b] != -1) chkmax(nxt[b+3*c+9],now[a+3*b]+a);
                }
            }
        }
        FOR(j,0,17) nxt[j] = std::min(nxt[j],4);
        if(nxt[9] >= 4 || nxt[18] >= 7) ::nxt[id][i] = 0;
        else ::nxt[id][i] = dfs(nxt);
    }
    return id;
}
int fac[MAXN],inv[MAXN];
inline void prework(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    std::vector<int> st(19,-1);//DEBUG(st.size());
    st[0] = st[18] = 0;
    dfs(st);
}
int cnt[MAXN];
int f[2][400+5][MAXN],now;

inline int C(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int main(){
    prework();
    int n;scanf("%d",&n);
//    DEBUG(C(3,2));
    FOR(i,1,13){
        int x;scanf("%d%*d",&x);
        cnt[x]++;
    }
    f[now=0][0][1] = 1;
    FOR(i,0,n-1){
        FOR(j,0,4*i){
            FOR(k,1,tot){
                FOR(x,0,4-cnt[i+1]){
                    add(f[now^1][j+x][nxt[k][x+cnt[i+1]]],1ll*f[now][j][k]*C(4-cnt[i+1],x)%ha);
                }
            }
        }
        CLR(f[now],0);now^=1;
    }
    int ans = 0;
    FOR(j,0,4*n-13){
        FOR(k,1,tot){
            add(ans,1ll*f[now][j][k]*fac[j]%ha*fac[4*n-13-j]%ha);
        }
    }
    ans = 1ll*ans*inv[4*n-13]%ha;
    printf("%d\n",ans);
    return 0;
}
/*
先考虑如何做判定性问题：f[i][0/1][j][k] 表示考虑前 i 种花色 是否选择出了对子 选了多少个 i-2 i-1 i 选了多少个 i-1 i i+1
接下来枚举选了多少个 i i+1 i+2 转移即可
于是 我们 dp of dp 设 F[i][j][S] 表示考虑了前 i 种花色 选择了 j 张 dp 状态为 S 的方案数为多少 转移一下就好了
答案就是枚举所有 S 不为胡的状态统计一下 和 最后除去(4n-13)!
*/
