/*
 * Time: 2019-11-12 15:53:18
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

const int MAXN = 500+5;
const int ha = 1e9 + 7;
int A[MAXN],B[MAXN],n,c;
int f[MAXN][MAXN],g[MAXN][MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int main(){
    scanf("%d%d",&n,&c);
    FOR(i,1,n) scanf("%d",A+i);
    FOR(i,1,n) scanf("%d",B+i);
    /*FOR(i,1,n){
        FOR(j,0,c){
            FOR(k,A[i],B[i]) (g[i][j] += qpow(k,j)) %= ha;
        }
    }*/
    FOR(i,1,n){
        FOR(k,A[i],B[i]){
            int now = 1;
            FOR(j,0,c){
                (g[i][j] += now) %= ha;
                now = 1ll*now*k%ha;
            }
        }
    }
    FOR(i,0,c) f[1][i] = g[1][i];
    FOR(i,2,n){
        FOR(j,0,c){
            FOR(k,0,j){
                (f[i][j] += 1ll*f[i-1][j-k]*g[i][k]%ha) %= ha;
            }
        }
    }
    printf("%d\n",f[n][c]);
    return 0;
}
