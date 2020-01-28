/*
 * Time: 2019-11-28 12:55:41
 */
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
#define int LL
int f[MAXN],S[MAXN],n,L;
std::deque<int> q;
#define X(i) (S[i])
#define Y(i) (f[i]+(S[i]+L)*(S[i]+L))

inline bool headpop(int i,int j,int k){ // j < k
    return Y(j)-Y(k) > 2*S[i]*(X(j)-X(k));
}

inline bool tailpop(int i,int j,int k,int l){ // j < k < l
    return (Y(j)-Y(k))*(X(k)-X(l)) > (Y(k)-Y(l))*(X(j)-X(k));
}

signed main(){
//    freopen("a.in","r",stdin);
    scanf("%lld%lld",&n,&L);L++;
    FOR(i,1,n){
        int x;scanf("%lld",&x);
        S[i] = S[i-1]+x;
    }
    FOR(i,1,n) S[i] += i;
    f[0] = 0;q.pb(0);
    FOR(i,1,n){
        while((int)q.size() >= 2 && headpop(i,q[0],q[1])) q.pop_front();
        int j = q.front();
        f[i] = f[j]+(S[i]-S[j]-L)*(S[i]-S[j]-L);
        while((int)q.size() >= 2 && tailpop(i,q[q.size()-2],q[q.size()-1],i)) q.pop_back();
        q.pb(i);
    }
    printf("%lld\n",f[n]);
    return 0;
}
