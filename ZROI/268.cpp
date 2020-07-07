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

const int MAXN = 100+5;
const int MAXM = 8;
const int ha = 1e9 + 7;
const int inv2 = (ha+1)/2;
int pw[MAXM+1];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

int a[MAXN][MAXN];
int n,m;

inline int det(){
    int ans = 1;
    FOR(i,1,n-1){
        int ps = -1;
        FOR(j,i,n-1){
            if(a[j][i]){
                ps = j;break;
            }
        }
        if(ps == -1) break;
        if(ps != i) std::swap(a[ps],a[i]),ans = ha-ans;
        int inv = qpow(a[i][i]);
        FOR(j,i+1,n-1){
            if(!a[j][i]) continue;
            int t = 1ll*inv*a[j][i]%ha;
            FOR(k,i,n-1) (a[j][k] += ha-1ll*a[i][k]*t%ha) %= ha;
        }
//       FOR(i,1,n-1) FOR(j,1,n-1) printf("%d%c",a[i][j]," \n"[j==n-1]);
    }
    FOR(i,1,n-1) ans = 1ll*ans*a[i][i]%ha;
    return ans;
}

struct Edge{
    int u,v,w;
}e[MAXN*MAXN];

int main(){
    pw[0] = 1;FOR(i,1,MAXM) pw[i] = pw[i-1]*3;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    int ans = 0;
    FOR(i,0,MAXM){
        CLR(a,0);
        FOR(j,1,m){
            int t = (e[j].w/pw[i])%3;
            if(t == 0) continue;
            a[e[j].u][e[j].u]++;a[e[j].v][e[j].v]++;
            a[e[j].u][e[j].v]--;a[e[j].v][e[j].u]--;
        }
        FOR(i,1,n) FOR(j,1,n) (a[i][j] += ha) %= ha;
        //if(i == 4){
      //      FOR(i,1,n) FOR(j,1,n) printf("%d%c",a[i][j]," \n"[j==n]);
    //        DEBUG(i);
  //      }
        int t1 = det();
        CLR(a,0);
        FOR(j,1,m){
            int t = (e[j].w/pw[i])%3;
            if(t == 0) continue;
            if(t == 1) a[e[j].u][e[j].v]--,a[e[j].v][e[j].u]--,a[e[j].u][e[j].u]++,a[e[j].v][e[j].v]++;
            else a[e[j].u][e[j].v]++,a[e[j].v][e[j].u]++,a[e[j].u][e[j].u]--,a[e[j].v][e[j].v]--;
        }
        FOR(i,1,n) FOR(j,1,n) (a[i][j] += ha) %= ha;
        int t2 = det();
        // odd+even = t1
        // even-odd = t2
        // 2even = t1+t2
        int even = 1ll*inv2*(t1+t2)%ha,odd = (t1+ha-even)%ha;
        (ans += 1ll*even*pw[i]%ha) %= ha;
        (ans += 1ll*odd*2%ha*pw[i]%ha) %= ha;
    }
    printf("%d\n",ans);
    return 0;
}
