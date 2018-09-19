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

const int MAXN = 300 + 5;

int N,M,K;
double ans;
double p[MAXN],q[MAXN*MAXN*MAXN];

int main(){
    scanf("%d%d%d",&N,&M,&K);
    p[0] = q[0] = 1;
    FOR(i,1,N){
        p[i] = p[i-1]*(N-i+1)/i;
    }
    FOR(i,1,M){
        q[i] = q[i-1]*(K-i+1)/(M-i+1);
    }
    FOR(r,0,N){
        FOR(c,0,N){
            int num = N*(r+c)-r*c;
            if(num > K) continue;
            ans += p[r]*p[c]*q[num];
        }
    }
    if(ans > 1e99) ans = 1e99;
    printf("%.10f",ans);
    system("sleep 11");
    return 0;
}