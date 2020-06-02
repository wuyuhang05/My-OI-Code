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
std::mt19937 g(time(NULL));
int main(){
    freopen("a.in","w",stdout);
    int n = 1e6,k = 1,s = 1e6;
    printf("%d %d %d\n",n,k,s);
    FOR(i,2,n) printf("%d ",1+g()%(i-1));puts("");
    FOR(i,1,n) printf("%d ",g()%2);puts("");
    return 0;
}
