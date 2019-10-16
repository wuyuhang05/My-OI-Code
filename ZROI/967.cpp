/*
 * Author: RainAir
 * Time: 2019-10-01 19:20:41
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

#define lowbit(x) ((x)&(-(x)))
const int MAXN = 1e6 + 5;
const int MAXM = 20+2;
int n,m;
char str[MAXN];
int a[MAXN];
int cnt[MAXM];
int pc[MAXN];

int main(){
    scanf("%d",&n);
    scanf("%s",str+1);
    FOR(i,1,n) a[i] = str[i]-'0';
    FOR(i,2,MAXN-1) pc[i] = pc[i>>1]+1;
    int sg = 0;
    FOR(i,1,n){
        if(a[n-i+1]){
            sg ^= lowbit(i);
            FOR(j,0,19){
                if((1<<j)&i) ++cnt[j];
            }
        }
    }
    scanf("%d",&m);
    FOR(i,1,m){
        int x;scanf("%d",&x);
        sg ^= lowbit(n-x+1);a[x] ^= 1;
        FOR(j,0,19){
            if((n-x+1)&(1<<j)) cnt[j] += a[x] ? 1 : -1;
        }
      //  DEBUG(sg);
        printf("%d\n",sg?cnt[pc[sg]]:0);
    }
    return 0;
}
