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

const int MAXN = 2000+2;
LL a[102][MAXN];
int m,n;

inline void Solve(){
    scanf("%d%d",&m,&n);
    FOR(i,1,m) FOR(j,1,n) scanf("%lld",&a[i][j]);
    FOR(i,1,m) std::sort(a[i]+1,a[i]+n+1);
    FOR(i,2,m){
        std::priority_queue<LL> q;
        FOR(j,1,n) q.push(a[i-1][1]+a[i][j]);
        FOR(j,2,n){
            FOR(k,1,n){
                if(q.top() > a[i-1][j]+a[i][k]){
                    q.pop();q.push(a[i-1][j]+a[i][k]);
                }
                else break;
            }
        }
        FOR(j,1,n) a[i][n-j+1] = q.top(),q.pop();
    }
    FOR(i,1,n) printf("%lld%c",a[m][i],(i == n) ? '\n' : ' ');
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
