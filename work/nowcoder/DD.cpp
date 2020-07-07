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
#define db double
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

const int MAXN = 1e5 + 5;

bool p[MAXN];
int prime[MAXN],cnt;

inline void prework(){
    FOR(i,2,MAXN-1){
        if(!p[i]) prime[++cnt] = i;
        for(int j = 1;j <= cnt && i*prime[j] < MAXN;++j){
            p[i*prime[j]] = 1;
            if(!(i%prime[j])) break;
        }
    }
}

const int ha = 1e9 + 7;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

int main(){
    prework();
    int n;scanf("%d",&n);
    int cnt = 0,sm = 0;
    while(sm+prime[cnt+1] <= n) cnt++,sm += prime[cnt];
    n -= sm;
    int ans = qpow(2,cnt);
    bool flag = 1;
    if(n <= 1) flag = 0;
//    FOR(i,1,cnt) if(n == prime[i]){flag = 0;break;}
    if(flag){
        int t = cnt;
        FOR(i,1,cnt) if(!(n%prime[i])) t--;
        (ans += qpow(2,t));
    }
    printf("%d\n",ans);
    return 0;
}
