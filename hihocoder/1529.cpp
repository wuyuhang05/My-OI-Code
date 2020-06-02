#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e5 + 5;
int n;
std::priority_queue<int> q;//斜率定义为比它 大的元素的个数

int main(){
    scanf("%d",&n);LL ans = 0;
    FOR(i,1,n){
        int x;scanf("%d",&x);x = -x;q.push(x);
        if(x < q.top()) ans += q.top()-x,q.pop(),q.push(x);
    }
    printf("%lld\n",ans);
    return 0;
}
