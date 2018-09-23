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

const int MAXN = 2000 + 5;

int f[MAXN][MAXN],w[MAXN];
int N,M;
char str[MAXN],wall[MAXN];

int main(){
    scanf("%s%s",str,wall);
    N = strlen(str)-1;M = strlen(wall);
    FOR(i,0,N){
        int t = 0;
        w[i] = -1;
        FOR(j,i,N){
            if(str[j] == wall[t]) t++;
            if(t == M){
                w[i] = j-i+1;
                break;
            }
        }
    }
    FOR(i,0,N){
        FOR(j,0,i){
            f[i+1][j] = std::max(f[i+1][j],f[i][j]);
            f[i+1][j+1] = std::max(f[i+1][j+1],f[i][j]);
            if(w[i] > 0) f[i+w[i]][j+w[i]-M] = std::max(f[i+w[i]][j+w[i]-M],f[i][j]+1);
        }
    }
    FOR(i,0,N+1)
        printf("%d%c",f[N+1][i],(i == N+1) ? '\n' : ' ');
    return 0;
}