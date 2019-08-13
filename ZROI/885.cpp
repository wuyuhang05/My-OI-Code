/*
 * Author: RainAir
 * Time: 2019-08-07 18:44:34
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
int n,m;
char A[MAXN][MAXN],B[MAXN][MAXN];
int sm1[MAXN],sm2[MAXN],col[MAXN][MAXN];
int vis1[MAXN],vis2[MAXN],vis[MAXN][MAXN];

std::queue<P> q;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%s",A[i]+1);
    FOR(i,1,n) scanf("%s",B[i]+1);
    bool fg = true;
    FOR(i,1,n) FOR(j,1,m) if(A[i][j] != B[i][j]) fg = false;
    if(fg){
        puts("1");
        return 0;
    }
    FOR(i,1,n) FOR(j,1,m) sm1[i] += (B[i][j] == 'X'),sm2[j] += (B[i][j] == 'X'),
        col[i][j] = (B[i][j] == 'X');
    FOR(i,1,n) FOR(j,1,m) if(sm1[i] == 1 && sm2[j] == 1 && B[i][j] == 'X') q.push(MP(i,j)),vis[i][j] = true;
    while(!q.empty()){
        P v = q.front();q.pop();
        // 尝试行和列的灰点
        if(vis1[v.fi] <= 1){
            vis1[v.fi]++;
            FOR(i,1,m){
                if(col[v.fi][i] == 1){
                    sm1[v.fi]--;sm2[i]--;
                }
                col[v.fi][i] = 2;
            }
            FOR(i,1,m){
                if(sm1[v.fi] == 0 && sm2[i] == 0 && !vis[v.fi][i]){
                    vis[v.fi][i] = 1;q.push(MP(v.fi,i));
                }
            }
        }
        if(vis2[v.se] <= 1){
            vis2[v.se]++;
            FOR(i,1,n){
                if(col[i][v.se] == 1) sm1[i]--,sm2[v.se]--;
                col[i][v.se] = 2;
            }
            FOR(i,1,m){
                if(sm1[i] == 0 && sm2[v.se] == 0 && !vis[i][v.se]){
                    vis[i][v.se] = true;q.push(MP(i,v.se));
                }
            }
        }
    }
    fg = 0;
    FOR(i,1,n) if(vis1[i]){
        FOR(j,1,m) if(vis2[j]){
            if(A[i][j] == 'O') fg = true;
        }
    }
    if(!fg){
        puts("0");return 0;
    }
    FOR(i,1,n) if(!vis1[i]){
        FOR(j,1,m) if(!vis2[j]){
            if(A[i][j]!= B[i][j]){
                puts("0");return 0;
            }
        }
    }
    puts("1");
    return 0;
}
