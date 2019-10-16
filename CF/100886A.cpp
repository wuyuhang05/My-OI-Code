/*
 * Author: RainAir
 * Time: 2019-10-10 08:00:41
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

const int MAXN = 400 + 5;
const int ZERO = 30;
const int MAXM = 4030;

std::bitset<60> f[MAXN][MAXM+1];
//处理到前 i 个数，第一个放了 j，其余两个的差是 x(-30 <= x <= 30)
int n,a[MAXN],id[MAXN],sm;
std::vector<int> vv[4];

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),id[i] = i,sm += a[i];
    std::sort(id+1,id+n+1,[](int x,int y) -> bool{
              return a[x] < a[y];
              });
    f[0][0].set(ZERO);
    FOR(i,0,n-1){
        int x = a[id[i+1]];
        FOR(j,0,MAXM){
            if(j+x <= MAXM) f[i+1][j+x] |= f[i][j];
            f[i+1][j] |= f[i][j] << x;
            f[i+1][j] |= f[i][j] >> x;
        }
    }
    int ans = 1e9,x = 0,y = 0,z = 0;
    FOR(i,0,MAXM){
        FOR(j,0,59){
            if(f[n][i][j]){
                int k = (sm-i-(j-ZERO))/2,l = (sm-i+(j-ZERO))/2;
                int gx = std::max(i,std::max(k,l))-std::min(i,std::min(k,l));
                if(gx < ans){
                    ans = gx;x = i;y = j;
                }
            }
        }
    }
    ROF(i,n,1){
        int v = a[id[i]];
        if(x-v >= 0 && f[i-1][x-v][y]){
            vv[1].pb(id[i]);
            x-= v;
        }
        else if(y-v >= 0 && f[i-1][x][y-v]){
            vv[2].pb(id[i]);
            y -= v;
        }
        else if(y+v < 60 && f[i-1][x][y+v]){
            vv[3].pb(id[i]);
            y += v;
        }
    }
    printf("%d\n",ans);
    FOR(i,1,3){
        printf("%lu ",vv[i].size());
        for(auto x:vv[i]) printf("%d ",x);
        puts("");
    }
    return 0;
}
