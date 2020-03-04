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

const int MAXN = 300000 + 5;

int N,M,Q;
int pep[MAXN*2],a[MAXN*2],p[MAXN*2];
int win[MAXN],lose[MAXN],tp;

bool cmp(int x,int y){
    if(a[x] == a[y]) return x < y;
    return a[x] > a[y];
}

void merge(){
    int i = 1,j = 1;
    int t = 0;
    // FOR(i,1,N) printf("%d ",win[i]);
    // FOR(i,1,N) printf("%d ",lose[i]);
    while(i <= N && j <= N){
        if(cmp(win[i],lose[j]))
            pep[++t] = win[i++];
        else
            pep[++t] = lose[j++];
        // DEBUG(i);DEBUG(j);DEBUG(pep[t]);
    }
    while(i <= N) pep[++t] = win[i++];
    while(j <= N) pep[++t] = lose[j++];
    
}

int main(){
    scanf("%d%d%d",&N,&M,&Q);
    FOR(i,1,2*N) pep[i] = i;
    FOR(i,1,2*N) scanf("%d",a+i);
    FOR(i,1,2*N) scanf("%d",p+i);
    // FOR(i,1,2*N) printf("%d ",pep[i]);
    std::sort(pep+1,pep+N*2+1,cmp);
    // FOR(i,1,2*N) printf("%d ",pep[i]);
    FOR(i,1,M){
        tp = 0;
        FOR(j,1,N){
            int x = pep[j*2],y = pep[j*2-1];
            if(p[x] > p[y]){
                a[x]++;
                win[++tp] = x;
                lose[tp] = y;
            }
            else{
                a[y]++;
                win[++tp] = y;
                lose[tp] = x;
            }
        }
        merge();
        // FOR(i,1,2*N) printf("%d ",pep[i]);
        // puts("");
    }
    printf("%d\n",pep[Q]);
    return 0;
}
