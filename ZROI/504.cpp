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
#define db double
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500+5;
const int ha = 7;
int N,a[MAXN],c[MAXN];
int p[MAXN],ans;
int v[6],n[6];
int f[MAXN][MAXN][7],g[MAXN][MAXN][7];

inline int mod(int x){
    if(x > ha) x -= ha;
    return x;
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N) scanf("%d",a+i),a[i] = 7-a[i];
    ROF(i,N+1,1){
        a[i] -= a[i-1];
        while(a[i] < 0) a[i] += ha;
        a[i] %= ha;
        p[a[i]]++;
    }
    ans += std::min(p[1],p[6]);
    v[1] = p[1] < p[6] ? 6 : 1;
    n[1] = std::max(p[1],p[6]) - std::min(p[1],p[6]);
    ans += std::min(p[2],p[5]);
    v[2] = p[2] < p[5] ? 5 : 2;
    n[2] = std::max(p[2],p[5]) - std::min(p[2],p[5]);
    ans += std::min(p[3],p[4]);
    v[3] = p[3] < p[4] ? 4 : 3;
    n[3] = std::max(p[3],p[4]) - std::min(p[3],p[4]);
    ans += n[1]+n[2]+n[3];
    CLR(g,-1);g[0][0][0] = 0;
    FOR(i,0,n[1]){
        CLR(f,-1);
        FOR(j,0,n[2]){
            FOR(k,0,n[3]){
                FOR(r,0,6){
                    if(g[j][k][r] == -1) continue;
                    if(i+1 <= n[1]){
                        int t = (r+v[1]+14)%7;
                        f[j][k][t] = std::max(f[j][k][t],g[j][k][r]+(!t));
                    }
                    if(j+1 <= n[2]){
                        int t = (r+v[2]+14)%7;
                        g[j+1][k][t] = std::max(g[j+1][k][t],g[j][k][r]+(!t));
                    }
                    if(k+1 <= n[3]){
                        int t = (r+v[3]+14)%7;
                        g[j][k+1][t] = std::max(g[j][k+1][t],g[j][k][r]+(!t));
                    }
                }
            }
        }
        if(i < n[1]){
            FOR(j,0,n[2]){
                FOR(k,0,n[3]){
                    FOR(r,0,6){
                        g[j][k][r] = f[j][k][r];
                    }
                }
            }
        }
    }
    ans -= g[n[2]][n[3]][0];
    printf("%d\n",ans);
    return 0;
}