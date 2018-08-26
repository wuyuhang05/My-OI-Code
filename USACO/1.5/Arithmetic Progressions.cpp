/*
ID: wuyuhan5
PROG: ariprog
LANG: C++
*/
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

#define LL long long
#define U unsigned
#define P std::pair<int,int>
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define SFOR(i,a,b,c) for(int i = a;i <= b;i += c)
#define RFOR(i,a,b) for(int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 30 + 5;
const int MAXM = 250 + 5;

bool f[MAXM*MAXM*2];
int N,M;
P ans[MAXM*MAXM*2];
int cnt,num;

bool cmp(P a,P b){
    if(a.second == b.second) return a.first < b.first;
    return a.second  < b.second;
}

int main(){
    freopen("ariprog.in","r",stdin);
    freopen("ariprog.out","w",stdout);
    scanf("%d%d",&N,&M);
    FOR(i,0,M)
        FOR(j,0,M)
            f[i*i+j*j] = 1;
    int MM = M*M*2;
    FOR(i,0,MM){
        if(!f[i]) continue;
        FOR(j,i+1,MM){
            if(!f[j]) continue;
            int sum = 0,gc = j-i;
            int last = i + (N-1) * gc;
            if(last > MM) break;
            SFOR(k,i,last,gc){
                if(f[k]) sum++;
                else break;
            }
            if(sum == N){
                ans[++cnt].first = i;
                ans[cnt].second = gc;
                num++;
            }
        }
    }
    if(!num){
        puts("NONE");
        return 0;
    }
    std::sort(ans + 1,ans + cnt + 1,cmp);
    FOR(i,1,cnt){
        printf("%d %d\n",ans[i].first,ans[i].second);
    }
    return 0;
}
