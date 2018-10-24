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
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 10000 + 5;
bool vis[MAXN+10];
int prime[MAXN],cnt;

void pre(){
    vis[1] = vis[0] = true;
    FOR(i,2,MAXN){
        if(!vis[i]) prime[++cnt] = i;
        for(int j = 1;j <= cnt && prime[j]*i <= MAXN;j++){
            vis[prime[j]*i] = 1;
            if(!(i%prime[j])) break;
        }
    }
}

inline int calc(int x,int pos){
    char str[10]={0};
    sprintf(str,"%d",x);
    str[pos] = '0';
    int res;
    sscanf(str,"%d",&res);
    return res;
}

int dist[MAXN+10];

inline int bfs(int a,int b){
    std::queue<int> q;
    q.push(a);
    dist[a] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();//DEBUG(v);
        if(v == b) return dist[v];
        int BASE = 1000;
        FOR(i,0,3){
            int x = calc(v,i);//DEBUG(x);
            FOR(j,0,9){
                if(!i && !j)continue;
                int h = x+BASE*j;
                if(!vis[h] && !dist[h]){
                    dist[h] = dist[v]+1;
                    q.push(h);
                }
            }
            BASE /= 10;
        }
    }
    return 0;
}

int main(){
    int a,b;pre();
    scanf("%d%d",&a,&b);
    printf("%d\n",bfs(a,b)-1);
    return 0;
}