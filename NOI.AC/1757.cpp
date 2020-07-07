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
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 40+2;
const int ha = 998244353;
const int M = MAXN*MAXN;

int n,m;
int a[MAXN],b[MAXN],A[MAXN],B[MAXN];
bool used[MAXN];
int f[2][MAXN][MAXN][2*M+3];
//  处理 i 个 j 个 a 往后 k 个 p 往后 值是 w
int now;

inline void add(int &x,int y){
    (x += y);if(x >= ha) x -= ha;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n) scanf("%d",b+i),B[i] = 1;
    FOR(i,1,n){
        if(b[i] == -1){
            A[a[i]]++;
        }
        else m -= std::abs(a[i]-b[i]),B[b[i]] = 0;
    }
    if(m < 0){
        puts("0");
        return 0;
    }
    f[now = 0][0][0][M] = 1;
    FOR(i,1,n){
        while(A[i]--){
            CLR(f[now^1],0);
            FOR(j,0,n){
                FOR(k,0,n){
                    FOR(w,0,2*M){
                        if(!f[now][j][k][w]) continue;
                        if(k && w+i <= 2*M) add(f[now^1][j][k-1][w+i],1ll*f[now][j][k][w]*k%ha);
                        if(w-i >= 0 && j+1 <= n) add(f[now^1][j+1][k][w-i],f[now][j][k][w]);
                    }
                }
            }
            now ^= 1;
        }
        if(B[i]){
            CLR(f[now^1],0);
            FOR(j,0,n){
                FOR(k,0,n){
                    FOR(w,0,2*M){
                        if(!f[now][j][k][w]) continue;
                        if(j && w+i <= 2*M) add(f[now^1][j-1][k][w+i],1ll*f[now][j][k][w]*j%ha);
                        if(k+1 <= n && w-i >= 0) add(f[now^1][j][k+1][w-i],f[now][j][k][w]);
                    }
                }
            }
            now ^= 1;
        }
    }
//    DEBUG(f[now][0][0][M+1]);
    int ans = 0;
    FOR(i,0,m) add(ans,f[now][0][0][i+M]);
    printf("%d\n",ans);
    return 0;
}
