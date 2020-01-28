/*
 * Time: 2019-12-01 19:59:51
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 10+3;
int n,m,k;
int a[MAXN][MAXN];

P p[MAXN];
int f[MAXN][MAXN][(1<<MAXN)+1];
// (i,j) root S connected

struct Node{
    int x,y,S;
    Node(int x=0,int y=0,int S=0) : x(x),y(y),S(S) {}
}pre[MAXN][MAXN][(1<<MAXN)+1];

std::queue<P> q;
bool inq[MAXN][MAXN];
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

inline void spfa(int S){
    while(!q.empty()){
        P v = q.front();q.pop();
        inq[v.fi][v.se] = 0;
        FOR(i,0,3){
            int xx = v.fi+dx[i],yy = v.se+dy[i];
            if(xx >= 1 && xx <= n && yy >= 1 && yy <= m){
                if(f[xx][yy][S] > f[v.fi][v.se][S]+a[xx][yy]){
                    f[xx][yy][S] = f[v.fi][v.se][S]+a[xx][yy];
                    pre[xx][yy][S] = Node(v.fi,v.se,S);
                    if(!inq[xx][yy]){
                        inq[xx][yy] = true;
                        q.push(MP(xx,yy));
                    }
                }
            }
        }
    }
}

bool ans[MAXN][MAXN];

inline void dfs(int x,int y,int S){
    ans[x][y] = 1;
    Node t = pre[x][y][S];
    if(!t.x || !t.y) return;
    dfs(t.x,t.y,t.S);
    if(t.x == x && t.y == y) dfs(t.x,t.y,S-t.S);
}

int main(){
    scanf("%d%d",&n,&m);
    CLR(f,0x3f);k = 0;
    FOR(i,1,n){
        FOR(j,1,m){
            scanf("%d",&a[i][j]);
            if(!a[i][j]) f[i][j][1<<k] = 0,p[k++] = MP(i,j);
        }
    }
    //DEBUG(1);
    if(k == -1){
        puts("0");
        FOR(i,1,n){
            FOR(j,1,m) printf("_ ");
            puts("");
        }
        return 0;
    }
    FOR(S,0,(1<<k)-1){
        FOR(i,1,n){
            FOR(j,1,m){
                for(int T = S;T;T = S&(T-1)){
                    int gx = f[i][j][T]+f[i][j][S-T]-a[i][j];
                    if(gx < f[i][j][S]){
                        pre[i][j][S] = Node(i,j,T);
                        f[i][j][S] = gx;
                    }
                }
                q.push(MP(i,j));inq[i][j] = 1;
            }
        }
        spfa(S);
    }
    dfs(p[0].fi,p[0].se,(1<<k)-1);
    printf("%d\n",f[p[0].fi][p[0].se][(1<<k)-1]);
    FOR(i,1,n){
        FOR(j,1,m){
            putchar(ans[i][j] ? (a[i][j] ? 'o' : 'x') : '_');
        }
        puts("");
    }
    return 0;
}

