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

const int MAXN = 2000 + 5;

int pre[MAXN],next[MAXN],N;
char a[MAXN],b[MAXN];
#define MP std::make_pair
std::vector<std::pair<int,int> > v;

#define calc(i,j) (i <= j) ? j - i : j - i + N

inline int get(){
    FOR(i,1,N){
        int now=i;
        while(!(b[now]-'0')) if(!--now) now = N;
        pre[i] = now;now=i;
        while(!(b[now]-'0')) if(++now > N) now = 1;
        next[i] = now;
    }
    int res=INT_MAX;
    FOR(pos,0,N-1){
        v.clear();
        int cnt = 0;
        FOR(i,1,N){
            int j = (i + pos) > N ? i+pos-N : i+pos;
            if(a[i] == b[j]) continue;
            cnt++;
            if(i <= j && next[i] <= j && next[i] >= i) continue;
            if(i > j && (next[i] <= j || next[i] >= i)) continue;
            v.push_back(MP(calc(pre[i],i),calc(j,next[j])));
        }
        std::sort(v.begin(),v.end());
        int ans = v.size() ? INT_MAX : 0,max = 0;
        ROF(i,(int)v.size()-1,0){
            ans = std::min(ans,max+v[i].first);
            max = std::max(max,v[i].second);
        }
        res = std::min(ans*2+cnt+pos,res);
    }
    return res;
}

int main(){
    scanf("%s%s",a+1,b+1);
    N = strlen(a+1);bool flag = false;
    FOR(i,1,N) if(b[i]-'0') {flag = true;break;}
    if(!flag) {puts("-1");return 0;}
    int ans = get();
    std::reverse(a+1,a+N+1);std::reverse(b+1,b+N+1);
    printf("%d\n",std::min(ans,get()));
    return 0;
}