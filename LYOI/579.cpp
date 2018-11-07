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
#define P std::pair<int,int>
#define MP std::make_pair
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500000 + 5;

int N,M;

struct BIT{
#define lowbit(x) x&-x
    int num[MAXN];

    inline void add(int pos,int x){
        while(pos <= N){
            num[pos] += x;
            pos += lowbit(pos);
        }
    }

    inline int calc(int pos){
        int res = 0;
        while(pos){
            res += num[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
}bit;
std::map<int,int> last;
int ans[MAXN];
std::vector<P> query[MAXN]; 
int a[MAXN],p[MAXN],l,r;

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N) scanf("%d",a+i),p[i] = last[a[i]],last[a[i]] = i;
    FOR(i,1,M) scanf("%d%d",&l,&r),query[r].push_back(MP(l,i));
    FOR(i,1,N){
        if(p[p[p[i]]]) bit.add(p[p[p[i]]],1),bit.add(p[p[i]],-2),bit.add(p[i],1);
        else if(p[p[i]]) bit.add(p[p[i]],-2),bit.add(p[i],1);
        else if(p[i]) bit.add(p[i],1);
        FOR(j,0,(int)query[i].size()-1) ans[query[i][j].second] = bit.calc(i) - bit.calc(query[i][j].first-1);
    }
    FOR(i,1,M) printf("%d\n",ans[i]);
    return 0;
}
