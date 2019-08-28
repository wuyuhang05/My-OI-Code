/*
 * Author: RainAir
 * Time: 2019-08-25 14:57:19
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100+5;
const int MAXM = 11;
const int ha = 1e9 + 7;
int n,m,C,D,now=0;
int f[2][25][(1<<MAXM)+3];
char mp[MAXN][MAXM];

inline void Solve(){
    CLR(f,0);now = 0;
    FOR(i,0,n-1){
        scanf("%s",mp[i]);
    }
    f[now][0][(1<<m)-1] = 1;
    FOR(i,0,n-1){
        FOR(j,0,m-1){
            CLR(f[now^1],0);
            if(mp[i][j] != '0'){
                FOR(k,0,D){
                    FOR(S,0,(1<<m)-1){
                        if(k && (S&(1<<j)))
                            (f[now^1][k][S] += f[now][k-1][S]) %= ha;
                        (f[now^1][k][S^(1<<j)] += f[now][k][S]) %= ha;
                        if(j && !(S&(1<<j-1)) && (S&(1<<j)))
                            (f[now^1][k][S|(1<<j)|(1<<j-1)] += f[now][k][S]) %= ha;
                    }
                }
            }
            else{
                FOR(k,0,D){
                    FOR(S,0,(1<<m)-1)
                        if((1<<j) & S)
                            (f[now^1][k][S] += f[now][k][S]) %= ha;
                }
            }
            now ^= 1;
        }
    }
    int ans = 0;
    FOR(i,C,D) (ans += f[now][i][(1<<m)-1]) %= ha;
    printf("%d\n",ans);
}

int main(){
    while(~scanf("%d%d%d%d",&n,&m,&C,&D)) Solve();
    return 0;
}
