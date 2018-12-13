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

const int MAXN = 200000+5;
int a[MAXN];
int f[MAXN][30];
int lg[MAXN+213];
int N;

inline void pre(){
    lg[0] = -1;
    FOR(i,1,N){
        lg[i] = (i&(i-1)) ? lg[i-1] : lg[i-1]+1;
        f[i][0] = a[i];
    }
    //FOR(i,1,100) printf("%d ",lg[i]);
    int c = lg[N];
    FOR(i,1,c){
        FOR(j,1,N){
            f[j][i] = std::min(f[j][i-1],f[j+(1<<i-1)][i-1]);
        }
    }
}

inline int calc(int l,int r){
    int c = lg[r-l+1];
    return std::min(f[l][c],f[r-(1<<c)+1][c]);
}
const int ha = 1000000000+7;

inline void add(int &a,int b){
    a += b;
    if(a > ha) a -= ha;
}
int ans = 0;
int main(){
    scanf("%d",&N);
    FOR(i,1,N) scanf("%d",a+i);
    pre();//DEBUG(calc(2,5));
    FOR(l1,1,N){
        FOR(r1,l1,N){
            FOR(l2,r1+1,N){
                FOR(r2,l2,N){
                    // printf("min{[%d,%d],[%d,%d]} = %d\n",l1,r1,l2,r2,std::min(calc(l1,r1),calc(l2,r2)));
                    add(ans,std::min(calc(l1,r1),calc(l2,r2)));
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}