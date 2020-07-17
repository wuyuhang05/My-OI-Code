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

const int MAXN = 20+1;
int n;
char str[MAXN][MAXN];
int f[2][(1<<MAXN)+3],now;
int len[MAXN*2];
std::vector<int> vis[26];
bool used[21];

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%s",str[i]+1);
    now = 0;CLR(f[now],-0x3f);
    f[now=0][1] = str[n][n]=='a'?1:(str[n][n]=='b'?-1:0);
    int t = 0;
    FOR(i,1,n) len[++t] = i;ROF(i,n-1,1) len[++t] = i;
    // j == k-i+1
    ROF(k,2*n-2,1){
        now ^= 1;
        CLR(f[now],(k)&1?-0x3f:0x3f);
        FOR(S,1,(1<<len[k])-1){
            char t = 0;bool flag = 1;
            FOR(i,0,25) vis[i].clear();CLR(used,0);
            int sm = 0;
            FOR(i,0,len[k]-1){
                if(!((S>>i)&1)) continue;
                int x = i+1;++sm;
                if(k > n) x += k-n;
                int y = k-x+1;
                if(!t) t = str[x][y];
                if(t != str[x][y]){flag = 0;break;}
                if(x+1<=n) if(!used[x+1]) vis[str[x+1][y]-'a'].pb(x+1),used[x+1] = 1;
                if(y+1<=n) if(!used[x]) vis[str[x][y+1]-'a'].pb(x),used[x] = 1;
            }
            if(!flag) continue;
            FOR(i,0,25){
                if(vis[i].empty()) continue;
                int nxt = 0;
                for(auto x:vis[i]){
                    if(k+1 > n) x -= k+1-n;
                    nxt |= (1<<(x-1));
                }
                if(std::abs(f[now^1][nxt]) >= 1e9) continue;
                int gx = 0;
                if(t == 'a') gx = sm;
                if(t == 'b') gx = -sm;
                if((k)&1) f[now][S] = std::max(f[now][S],f[now^1][nxt]+gx);
                else f[now][S] = std::min(f[now][S],f[now^1][nxt]+gx);
            }
        }
        if(k == 8){
            FOR(S,1,(1<<len[k])-1){
                printf("%d %d\n",S,f[now][S]);
            }
        }
    }
    puts(f[now][1] > 0 ? "FIRST" : (f[now][1]==0 ? "DRAW":"SECOND"));
    return 0;
}
