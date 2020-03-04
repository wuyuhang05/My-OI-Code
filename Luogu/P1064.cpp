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

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 32000 + 5;
const int MAXM = 60 + 5;

int N,M;
int mv[MAXM],mp[MAXM],qv[MAXM][3],qp[MAXN][3];
int f[MAXN];

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,M){
        int v,p,q;
        scanf("%d%d%d",&v,&p,&q);
        if(!q){
            mv[i] = v;
            mp[i] = v*p;
        }
        else{
            qv[q][++qv[q][0]] = v;
            qp[q][++qp[q][0]] = v*p;
        }
    }
    FOR(i,1,M){
        RFOR(j,N,mv[i]){
            if(!mv[i]) break;
            f[j] = std::max(f[j],f[j-mv[i]] + mp[i]);
            if(j >= mv[i] + qv[i][1])
                f[j] = std::max(f[j],f[j-mv[i]-qv[i][1]]+mp[i]+qp[i][1]);
            if(j >= mv[i] + qv[i][2])
                f[j] = std::max(f[j],f[j-mv[i]-qv[i][2]]+mp[i]+qp[i][2]);
            if(j >= mv[i] + qv[i][1] + qv[i][2])
                f[j] = std::max(f[j],f[j-mv[i]-qv[i][1]-qv[i][2]] + mp[i] + qp[i][1] + qp[i][2]);
        }
    }
    printf("%d\n",f[N]);
    return 0;
}
