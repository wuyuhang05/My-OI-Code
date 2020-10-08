/*
 * Author: RainAir
 * Time: 2019-10-08 16:16:32
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
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 40+5;
const int MAXM = 5+7+5+1;
const int ha = 1e9 + 7;

int f[MAXN][(1<<MAXM)+3];
int n,x,y,z;

int main(){
    scanf("%d%d%d%d",&n,&x,&y,&z);
    int fin = (1<<(x+y+z-1))|(1<<(x+y-1))|(1<<(x-1));
    f[0][0] = 1;int U = (1<<(x+y+z))-1;
    FOR(i,0,n-1){
        FOR(S,0,U){
            if(!f[i][S]) continue;
            FOR(k,1,10){
                LL T = U&((S<<k)|(1<<(k-1)));
                if((T&fin) != fin){
                    (f[i+1][T] += f[i][S]) %= ha;
                }
            }
        }
    }
    int ans = 0;
    FOR(S,0,(1<<(x+y+z))-1) (ans += f[n][S])%=ha;
    int t = 1;FOR(i,1,n) t = 1ll*t*10%ha;
    ans = ha-ans;
    printf("%d\n",(ans+t)%ha);
    return 0;
}
