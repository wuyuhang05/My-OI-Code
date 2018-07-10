#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 200 + 5;

int ans[MAXN][MAXN],a[MAXN][MAXN],d[MAXN][MAXN],lisan[100000],t[MAXN][MAXN];

int N,T,S,E;
int cnt;

void floyd1(){
    for(int k = 1;k <= cnt;k++)
        for(int i = 1;i <= cnt;i++)
            for(int j = 1;j <= cnt;j++)
                d[i][j] = std::min(ans[i][k] + a[k][j],d[i][j]);
    memcpy(ans,d,sizeof(ans));
    memset(d,0x3f,sizeof(d));
}

void floyd2(){
    for(int k = 1;k <= cnt;k++)
        for(int i = 1;i <= cnt;i++)
            for(int j = 1;j <= cnt;j++)
                t[i][j] = std::min(t[i][j],a[i][k] + a[k][j]);
    memcpy(a,t,sizeof(a));
    memset(t,0x3f,sizeof(t));
}

int main(){
    scanf("%d%d%d%d",&N,&T,&S,&E);
    memset(ans,0x3f,sizeof(ans));
    memset(a,0x3f,sizeof(a));
    memset(d,0x3f,sizeof(d));
    memset(t,0x3f,sizeof(t));
    for(int i = 1;i <= 200;i++)
        ans[i][i] = 0;
    for(int u,v,w,i = 1;i <= T;i++){
        scanf("%d%d%d",&w,&u,&v);
        if(!lisan[u])
            lisan[u] = ++cnt;
        if(!lisan[v])
            lisan[v] = ++cnt;
        a[lisan[u]][lisan[v]] = a[lisan[v]][lisan[u]] = std::min(a[lisan[u]][lisan[v]],w);
    }
    while(N){
        if(N & 1) floyd1();
        floyd2();
        N >>= 1;
    }
    printf("%d\n",ans[lisan[S]][lisan[E]]);
    return 0;
}

