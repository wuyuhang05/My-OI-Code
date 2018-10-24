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

int N;
const int MAXN = 1000 + 5;
int m[MAXN][3];
int ans;

int main(){
    scanf("%d",&N);
    FOR(i,1,N){
        scanf("%d%d",&m[i][1],&m[i][2]);
    }
    int cnt = 0;
    FOR(i,1,N){
        if(!m[i][1] && !m[i][2]) cnt++;
        else{
            ans = std::max(ans,cnt*2);
            cnt = 0;
        }
    }
    printf("%d\n",std::max(ans,cnt*2));
    return 0;
}