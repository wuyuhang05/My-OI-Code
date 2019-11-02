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

const int MAXN = 500 + 5;
int f[2][MAXN][MAXN];
int n,p;

inline void add(int &a,int b){
    a += b;if(a >= p) a -= p;
}

inline void upd(int k,int x1,int y1,int x2,int y2,int d){
    add(f[k][x1][y1],d);add(f[k][x1][y2+1],p-d);
    add(f[k][x2+1][y1],p-d);add(f[k][x2+1][y2+1],d);
}

int now;

int main(){
    scanf("%d%d",&n,&p);
    upd(now=1,0,0,0,0,1);
    FOR(i,1,n-1){
        CLR(f[now^1],0);
        FOR(j,0,i+1){
            FOR(k,0,i+1){
                if(j) add(f[now][j][k],f[now][j-1][k]);
                if(k) add(f[now][j][k],f[now][j][k-1]);
                if(j && k) add(f[now][j][k],p-f[now][j-1][k-1]);
                int t = f[now][j][k];
                if(!t) continue;
                upd(now^1,j,k,j,k,t);
                upd(now^1,j+1,k,i,k,t);
                upd(now^1,j+1,k+1,j+1,j,t);
            }
        }
        now ^= 1;
    }
    int ans = 0;//now^=1;
    FOR(i,0,n+1){
        FOR(j,0,n+1){
            if(i) add(f[now][i][j],f[now][i-1][j]);
            if(j) add(f[now][i][j],f[now][i][j-1]);
            if(i && j) add(f[now][i][j],p-f[now][i-1][j-1]);
            add(ans,f[now][i][j]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
