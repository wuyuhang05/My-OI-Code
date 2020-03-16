#include<bits/stdc++.h>

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

const int MAXN = 700+5;
const int ha = 1e9 + 7;

inline void add(int &a,int b){
    (a += b);if(a >= ha) a -= ha;
}

char lim[MAXN];
int f[MAXN][MAXN][2];
int n;
int pw[MAXN];

inline void solve(int LIM){
    CLR(f,0);f[0][0][1] = 1;
    FOR(i,0,n-1){
        FOR(j,0,std::min(n,i)){
            FOR(k,0,1){
                if(!f[i][j][k]) continue;
                int up = k?(lim[i+1]-'0'):9;
                FOR(x,0,up){
                    add(f[i+1][j+(x>=LIM)][k&&(x==up)],f[i][j][k]);
                }
            }
        }
    }
}

int main(){
    scanf("%s",lim+1);n = strlen(lim+1);
    int ans = 0;
    pw[0] = 0;pw[1] = 1;
    FOR(i,2,MAXN-1) pw[i] = (pw[i-1]*10ll%ha+1)%ha;
    FOR(i,1,9){
        solve(i);
        FOR(j,1,n) add(f[n][j][0],f[n][j][1]); // 前导 0 保证统计了所有数字
        FOR(j,1,n) add(ans,1ll*f[n][j][0]*pw[j]%ha);
    }
    printf("%d\n",ans);
    return 0;
}
/*
 * key word:拆贡献 数位 dp
 * 考虑枚举计算每一个数字的贡献 数字 i 的贡献长成 i*\sum 10^j
 * 我们考虑让 i  的贡献在[1,i] 都被统计一次 那么现在就是枚举位i 所有>=i 的都会造成贡献
 * 那么考虑枚举当前要 >=j 令 f[i][k][0/1] 前 i 位 >=j 的有 k 位 是否卡上界的方案数 最后乘上11...(k 个 1) 即可
 * f[i][k][0/1] -> f[i+1][k+(x>=j)][0/1]
 * 为什么不能直接统计=i 的个数？因为这样很麻烦你需要多记录一下=i 的连续段在哪个位置 时间复杂度就爆炸了
 * 实际上对于这种题 排序后计算一个后缀是好计算的 就可以考虑把贡献均摊到后面
 * 或许做多了这种题后来就会了吧。。
 */
