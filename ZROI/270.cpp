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

const int MAXN = 20+1;
int f[2][(1<<MAXN)+3],now;
char str[MAXN];
int n;

inline int full(int l,int r){
    return (1<<(r+1))-(1<<l);
}

int main(){
    scanf("%s",str+1);n = strlen(str+1);
    int t = 0;
    FOR(i,0,n-1) t |= (str[i+1]-'0')<<i;
    f[now = 0][t] = 1;
    FOR(i,0,100000){
        if(f[now][0]){
            printf("%d\n",i);
            return 0;
        }
        memcpy(f[now^1],f[now],sizeof(f[now]));
        FOR(S,0,(1<<n)-1){
            if(!f[now][S]) continue;
            FOR(l,0,n-1){
                int r = std::min(n-1,l+i);
                f[now^1][S^full(l,r)] = 1;
            }
        }
        now ^= 1;
    }
    return 0;
}
