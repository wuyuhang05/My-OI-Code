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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000000+5;
const int ha = 19260817;
int a[MAXN],b[MAXN];
int sum[MAXN];
int N,M;

inline void add(int &a,int b){
    a += b;
    if(a > ha) a -= ha;
}

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N){
        int x;
        scanf("%d",a+i);
    }
    FOR(i,1,N){
        int x;scanf("%d",b+i);
    }
    FOR(i,1,N){
        add(sum[i],sum[i-1]);
        add(sum[i],(a[i]*b[i])%ha);
    }
    while(M--){
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",(sum[r]-sum[l-1]+ha)%ha);
    }
    return 0;
}
