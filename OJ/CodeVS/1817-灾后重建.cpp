#include <iostream>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 500 + 5;
#define INF 707406378
#define R register

int f[MAXN][MAXN],timer[MAXN];
int N,M,Q,i;
#define min(a,b) (a < b) ? a : b

inline void Read(int &x){
    static char ch;
    bool flag;
    for(flag = false,ch = getchar();ch < '0' || ch > '9';ch = getchar()) flag |= ch == '-';
    for(x = 0;isdigit(ch);ch = getchar()) x = (x << 1) + (x << 3) + ch - '0';
    x = flag ? -x : x;
}

inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

inline void Floyd(int k){
    for(R int i = 0;i < N;++i)
        for(R int j = 0;j < N;++j){
            f[i][j] = min(f[i][j],f[i][k] + f[k][j]);
        }
}

inline int dy(){
    Read(N);Read(M);
    for(R int i = 0;i < N;++i)
        Read(timer[i]);
    for(R int i = 0;i < N;++i){
        for(R int j = 0;j < N;++j)
            f[i][j] = INF;
        f[i][i] = 0;
    }
    for(R int i = 1;i <= M;++i){
        R int u,v,w;
        Read(u);Read(v);Read(w);
        f[u][v] = f[v][u] = w;
    }
    Read(Q);
    while(Q--){
        R int x,y,t;
        Read(x);Read(y);Read(t);
        while(timer[i] <= t && i < N){
            Floyd(i);
            ++i;
        }
        if(timer[x] > t || timer[y] > t || f[x][y] >= INF) write(-1);
        else write(f[x][y]);
        putchar('\n');
    }
    exit(0);
}
int QAQ = dy();
int main(){;}
