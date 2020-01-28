/*
 * Time: 2019-11-28 10:05:56
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

const int MAXN = 20+5;
int nxt[MAXN],ha,n,m;
char str[MAXN];

inline void prework(){
    nxt[1] = 0;
    FOR(i,2,m){
        int j = nxt[i-1];
        while(str[j+1] != str[i] && j){
            j = nxt[j];
        }
        if(str[j+1] == str[i]) nxt[i] = j+1;
        else nxt[i] = 0;
    }
}

// f[i][j] 填了前 i 位 匹配了 j 位
//  f[i][j] -> f[i+1][j+1]
//  f[i][j] -> f[i+1][nxt[j]]
// if(j == m) exit

struct Matrix{
    int a[MAXN][MAXN];

    Matrix(){CLR(a,0);}

    Matrix operator * (const Matrix &t) const {
        Matrix ans;
        FOR(i,0,m){
            FOR(j,0,m){
                FOR(k,0,m){
                    (ans.a[i][j] += 1ll*a[i][k]*t.a[k][j]%ha) %= ha;
                }
            }
        }
        return ans;
    }
}base;

inline Matrix qpow(Matrix a,int n){
    Matrix res;
    FOR(i,0,m) res.a[i][i] = 1;
    while(n){
        if(n & 1) res = res*a;
        a = a*a;
        n >>= 1;
    }
    return res;
}

int main(){
    scanf("%d%d%d",&n,&m,&ha);
    scanf("%s",str+1);
    prework();
    FOR(i,0,m-1){
        FOR(j,0,9){
            int k = i;
            while(k && (str[k+1]-'0') != j) k = nxt[k];
            if((str[k+1]-'0') == j) k++;
            if(k != m) base.a[i][k] = (base.a[i][k]+1)%ha;
        }
    }
//    FOR(i,0,m) FOR(j,0,m) printf("%d%c",base.a[i][j]," \n"[j==m]);
    int ans = 0;
    Matrix res = qpow(base,n-1);
//    DEBUG(n-1);
//    puts("");
//    FOR(i,0,m) FOR(j,0,m) printf("%d%c",res.a[i][j]," \n"[j==m]);
    FOR(i,0,m-1) (ans += (res.a[0][i]*9ll%ha+res.a[1][i])%ha) %= ha;
    printf("%d\n",ans);
    return 0;
}
