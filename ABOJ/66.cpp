#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 500000+5;
const int MAXM = 20 + 5;

int n,m,f[MAXN+10][MAXM+10],lg[MAXN+10];

inline int work(int i,int j){ // length:i, unused ball:j
    if(j > lg[i]) return lg[i]+1;
    if(f[i][j] != -1) return f[i][j];
    if(!i) return 0;if(!j) return INT_MAX;
    if(i == 1) return 1;if(j == 1) return i;
    int l = 2,r = i,ans = INT_MAX;
    while(l <= r){
        int mid = (l + r) >> 1,lf = work(mid-1,j-1),rf = work(i-mid,j);
        if(rf < lf){ // rf-lf < 0
            ans = std::min(ans,lf);
            r = mid-1;
        }
        else{
            ans = std::min(ans,rf);
            l = mid+1;
        }
    }
    return f[i][j] = ans+1;
}

inline int calc(int x){
    int res = 0;
    while(x){
        x /= 2;res++;
    }
    return res;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) lg[i] = calc(i)-1;
    CLR(f,-1);
    printf("%d\n",work(n,m));
    return 0;
}
