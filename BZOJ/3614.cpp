/*
 * Author: RainAir
 * Time: 2019-07-22 17:31:17
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

const int MAXN = 21;
const int MAXM = (1<<MAXN)+1;

int f[MAXM],n,N;
char str[MAXN];

inline void calc(){
    double c;int t = 0;
    scanf("%s %lf",str+1,&c);
    FOR(i,1,n) t <<= 1,t |= (str[i]=='+' ? 1 : 0);
    //f[t] = (int)(c*100);
    if(c > 0) f[t] = (int)(c*100+0.5);
    else f[t] = (int)(c*100-0.5);
}

inline void Lgy_AK_IOI(){ // non-recursive
    for(int i = 0;i < n;++i){
        int len = (1<<i);
        for(int j = 0;j < N;j += (len<<1)){
            FOR(k,0,len-1){
                int x = f[j+k],y = f[j+len+k];
                f[j+k] = (x+y);f[j+len+k] = (y-x);
            }
        }
    }
}
/*
inline int gcd(int a,int b){
    if(!b) return a;
    if(!a) return b;
    if(!(a&1) && !(b&1)) return 2*gcd(a>>1,b>>1);
    if(!(a&1)) return gcd(a>>1,b);
    if(!(b&1)) return gcd(a,b>>1);
    return gcd(b,a-b);
}*/

inline int gcd(int a,int b){
    return !b ? a : gcd(b,a%b);
}
int mu;
inline void print(int x,int y){
    if(!x) return;
    if(x < 0) putchar('-');x = std::abs(x);
    int t = gcd(x,mu);
    if(t == mu) printf("%d",x/mu);
    else printf("%d/%d",x/t,mu/t);
    if(y) putchar(' ');
    for(int i = 1;i <= n;++i,y <<= 1) if(y&(N>>1)) printf("x%d",i);
    putchar('\n');
}

inline void outans(int s,int x){
    int t = ((x<<1)|1)<<(n-s);
    print(f[t],t);if(s == n) return;
    outans(s+1,(x<<1)|1);outans(s+1,x<<1);
}

int main(){
 //   DEBUG(sizeof(f)/1024/1024);
    scanf("%d",&n);N = 1<<n;mu = 100<<n;
    FOR(i,1,N) calc();
    Lgy_AK_IOI();
    print(f[0],0);outans(1,0);
    return 0;
}
