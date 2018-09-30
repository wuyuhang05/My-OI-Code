#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1500 + 5;
const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};
int N,M,s,t;
int map[MAXN][MAXN];
int f[3][MAXN][MAXN];
bool flag;

void dfs(int x,int y,int rx,int ry){ // real x,real y.
    if(flag) return;
    if(f[0][x][y] && (f[1][x][y] != rx || f[2][x][y] != ry)){
        flag = 1;return;
    }
    f[0][x][y] = 1;f[1][x][y] = rx;f[2][x][y] = ry;
    FOR(i,0,3){
        int xx = (x + dx[i] + N)%N,yy = (y + dy[i] + M) % M;
        int rxx = rx + dx[i],ryy = ry + dy[i];
        if(!map[xx][yy]){
            if(!f[0][xx][yy] || f[1][xx][yy] != rxx || f[2][xx][yy] != ryy){
                dfs(xx,yy,rxx,ryy);
            }
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);    
    while(std::cin >> N >> M){
        CLR(f,0);CLR(map,0);
        flag = false;
        std::string str;
        FOR(i,0,N-1){
            std::cin >> str;
            // str = "@" + str;
            FOR(j,0,M-1){
                if(str[j] == '#') map[i][j] = 1;
                if(str[j] == 'S') s = i,t = j;
            }
        }
        dfs(s,t,s,t);
        if(flag) puts("Yes");
        else puts("No");
    }
    return 0;
}