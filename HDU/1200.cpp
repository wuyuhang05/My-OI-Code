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

const int MAXN = 16000000+5;
char str[MAXN];
int tap[19260817];
bool S[MAXN];
int N,BASE,ans;
//std::map<U LL,int> S;


int main(){
    scanf("%d%d",&N,&BASE);
    scanf("%s",str+1);
    int len = strlen(str+1),cnt = 0;
    FOR(i,1,len){
        if(!tap[str[i]]) tap[str[i]] = ++cnt;
        if(cnt == BASE) break;
    }
    FOR(i,1,len){
        int j = i+N-1;
        if(j > len) break;
        U LL hash = 0ll;
        FOR(k,i,j){
            hash = (hash * BASE) + tap[str[k]];
        }
        if(!S[hash]) S[hash] = 1,ans++;
    }
    printf("%d\n",ans);
    return 0;
}