/*
 USER: wuyuhan5
 LANG: C++
 PROB: wormhole
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 12 + 5;

int x[MAXN],y[MAXN],to[MAXN];
int p[MAXN];
int N,ans;

inline bool pd(){
    for(int i = 1;i <= N;i++){
        int pos = i;
        for(int j = 1;j <= N;j++){
            pos = to[p[pos]];
        }
        if(pos) return true;
    }
    return false;
}

void dfs(int step){
    int u=1,v;
    if(step > N){
        if(pd()) ans++;
        return;
    }
    while(p[u]) u++;
    for(v = u + 1;v <= N;v++){
        if(p[v]) continue;
        p[u] = v;p[v] = u;
        dfs(step + 2);
        p[u] = p[v] = 0;
    }
}

int main(){
    freopen("wormhole.in","r",stdin);
    freopen("wormhole.out","w",stdout);
    scanf("%d",&N);
    for(int i = 1;i <= N;i++)
        scanf("%d%d",x+i,y+i);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N;j++){
            if(y[i] == y[j] && x[j] > x[i]){
                if(!to[i] || x[j] - x[i] < x[to[i]] - x[i])
                    to[i] = j;
            }
        }
    }
    dfs(1);
    printf("%d\n",ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}

