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

const int MAXN = 100 + 2;
const int MAXM = 10 + 2;
const int ha = 1e9 + 7;

class RainbowGraph{
private:

public:
    int G[MAXN][MAXN];
    int f[MAXN][MAXM][MAXM][(1<<MAXM)+3],g[MAXN][(1<<MAXM)+3];
    std::vector<int> col[MAXN];
    int ps[MAXN];
    int n;
    int countWays(std::vector<int> color,std::vector<int> a,std::vector<int> b){
        FOR(i,0,(int)a.size()-1) G[a[i]][b[i]] = G[b[i]][a[i]] = 1;
        n = color.size();
        FOR(i,0,n-1) col[color[i]].pb(i),ps[i] = (int)col[color[i]].size()-1;
        FOR(c,0,9){
            int k = col[c].size();
            FOR(i,0,k-1) f[c][i][i][1<<i] = 1;
            FOR(S,0,(1<<k)-1){
                FOR(i,0,k-1){
                    FOR(j,0,k-1){
                        FOR(p,0,k-1){
                            if(!(S&(1<<p)) && G[col[c][j]][col[c][p]]){
                                (f[c][i][p][S|(1<<p)] += f[c][i][j][S]) %= ha;
                            }
                        }
                    }
                }
            }
        }
        FOR(c,0,9){
            int k = col[c].size();
            FOR(i,0,k-1){
                FOR(j,0,k-1){
                    (g[col[c][j]][1<<c] += f[c][i][j][(1<<k)-1]) %= ha;
                }
            }
        }
        FOR(S,0,(1<<10)-1){
            FOR(i,0,n-1){
                if(!g[i][S]) continue;
                //DEBUG(i);DEBUG(S);
                FOR(c,0,9){
                    if(!(S&(1<<c))){
                        FOR(j,0,(int)col[c].size()-1){
                            if(G[i][col[c][j]]){
                                FOR(q,0,(int)col[c].size()-1){
                                    (g[col[c][q]][S|(1<<c)] += 1ll*g[i][S]*f[c][j][q][(1<<(int)col[c].size())-1]%ha) %= ha;
                                }
                            }
                        }
                    }
                }
            }
        }
        int ans = 0,U = 0;
        FOR(i,0,9) if(col[i].size()) U |= (1<<i);
        FOR(i,0,n-1) (ans += g[i][U]) %= ha;
        return ans;
    }
};
/*
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    std::vector<int> a,b,c;
    FOR(i,1,n){
        int x;scanf("%d",&x);a.pb(x);
    }
    FOR(i,1,m){
        int x;scanf("%d",&x);b.pb(x);
    }
    FOR(i,1,m){
        int x;scanf("%d",&x);c.pb(x);
    }
    printf("%d\n",test.countWays(a,b,c));
    return 0;
}*/
