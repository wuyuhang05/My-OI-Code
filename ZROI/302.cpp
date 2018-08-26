#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define LL long long
#define U unsigned
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define RFOR(i,a,b) for(int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};
const int MAXN = 2000 + 5;
int N,M;

struct Place{
    int x,y,dist;
};

char str[MAXN];
int dist[MAXN][MAXN];
std::queue<Place> q;

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N){
        scanf("%s",str);
        FOR(j,0,M-1){
            if(str[j] == '.') dist[i][j+1] = INT_MAX;
            else if(str[j] == '+'){
                dist[i][j+1] = 0;
                q.push((Place){i,j+1,0});
            }
            else dist[i][j+1] = -1;
        }
    }
    while(!q.empty()){
        Place v = q.front();
        q.pop();
        FOR(i,0,3){
            int x = v.x+dx[i],y = v.y + dy[i];
            while(x >= 1 && x <= N && y >= 1 && y <= N && dist[x][y] != -1){
                if(dist[x][y] >= INT_MAX){
                    q.push((Place){x,y,v.dist+1});
                    dist[x][y] = v.dist+1;
                }       
                x += dx[i];y += dy[i];
            }   
        }
    }
    FOR(i,1,N)
        FOR(j,1,M){
            if(dist[i][j] == -1) putchar('#');
            else if(dist[i][j] == INT_MAX) putchar('X');
            else printf("%d",dist[i][j]);
            putchar((j == M) ? '\n' : ' ');
        }
    return 0;
}
