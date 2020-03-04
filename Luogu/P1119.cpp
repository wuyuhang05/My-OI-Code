#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <climits>
#include <queue>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl;

const int MAXN = 500 + 5;
const int INF = 1e9 + 7;
#define R register

int N,M,Q,i;
int f[MAXN][MAXN];
int timer[MAXN];

inline void Read(int &x){
    char ch = getchar();
    x = 0;
    int flag = 1;
    for(;!isdigit(ch);ch = getchar())
        if(ch == '-') flag = -1;
    for(;isdigit(ch);ch = getchar())
        x = (x << 1) + (x << 3) + ch - '0';
    x *= flag;
}

inline void floyd(int k){
    for(R int i = 0;i < N;++i)
        for(R int j = 0;j < N;++j)
            f[i][j] = std::min(f[i][j],f[i][k] + f[k][j]);
}

int main(){
    Read(N);Read(M);
    for(R int i = 0;i < N;++i)
        Read(timer[i]);
    for(R int i = 0;i < N;++i){
        for(int j = 0;j < N;++j)
            f[i][j] = INF;
        f[i][i] = 0;
    }
    for(R int u,v,w,i = 0;i < M;++i){
        Read(u);Read(v);Read(w);
        f[u][v] = f[v][u] = w;
    }
    Read(Q);
    while(Q--){
        R int x,y,t;
        Read(x);Read(y);Read(t);
        while(timer[i] <= t && i < N){
            floyd(i);
            ++i;
        }
        if(timer[x] > t || timer[y] > t || f[x][y] >= INF) printf("-1\n");
        else printf("%d\n",f[x][y]);
    }
    return 0;
}

