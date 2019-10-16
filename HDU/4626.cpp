/*
 * Author: RainAir
 * Time: 2019-08-28 11:43:37
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e6 + 5;
const int MAXL = 1e5 + 5;
char str[MAXL];
int a[MAXN],f[MAXN],pc[MAXN],n;

inline void FMT(){
    FOR(i,0,19){
        FOR(S,0,(1<<20)-1){
            if(!(S&(1<<i))) f[S] += f[S|(1<<i)];
        }
    }
}

inline void Solve(){
    CLR(f,0);
    scanf("%s",str+1);n = strlen(str+1);
    FOR(i,1,n) a[i] = (1<<(str[i]-'a'));
    FOR(i,1,n) a[i] ^= a[i-1];
    f[0]++;FOR(i,1,n) f[a[i]]++;
    FMT();int q;scanf("%d",&q);
    while(q--){
        int s = 0,k;scanf("%d",&k);
        FOR(i,1,k){
            scanf("%s",str+1);
            s |= (1<<(str[1]-'a')); // 需要变成 0 的
        }
        int s1 = s;LL ans = 0;
        do{ //  s1 枚举哪些强制为 1
            int s2 = s^s1,s3 = s2,cnt = 0; // s2 哪些是要容斥掉的 0
            do{ // s3 枚举哪些强制为 1(0 = (unlimited-1))
                cnt += (pc[s3]&1?-1:1)*f[s1|s3]; // 其他无限制 超集和
                s3 = (s3-1)&s2;
            }while(s2 != s3);
            ans += 1ll*cnt*(cnt-1)/2;
            s1 = (s1-1)&s;
        }while(s1 != s);
        printf("%lld\n",ans);
    }
}

signed main(){
    int tt = sizeof(str)+sizeof(a)+sizeof(f)+sizeof(pc);
//    DEBUG(tt/1024/1024);
    FOR(i,1,MAXN-1) pc[i] = pc[i>>1]+(i&1);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
