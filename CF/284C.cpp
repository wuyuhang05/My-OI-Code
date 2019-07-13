#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 2e5 + 5;
int a[MAXN],tot,n,tp,sum[MAXN];
std::stack<int> S;

signed main(){
    scanf("%lld",&n);S.push(0);
    FOR(i,1,n){
        int opt;scanf("%lld",&opt);
        if(opt == 2){
            int k;scanf("%lld",&k);
            S.push(k);tot += k;
        }
        if(opt == 1){
            int k,x;scanf("%lld%lld",&k,&x);
            sum[k] += x;
            tot += k*x;
        }
        if(opt == 3){
            LL v = S.top();tot -= v+sum[S.size()];
            sum[S.size()-1] += sum[S.size()];
            sum[S.size()] = 0;S.pop();
        }
        printf("%.10f\n",1.0*tot/S.size());
    }
    return 0;
}
