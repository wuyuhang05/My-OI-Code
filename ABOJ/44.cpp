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

const int MAXN = 1e5 + 5;
int n,a[MAXN],p[MAXN],f[MAXN],mark[MAXN];
int res;

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),p[a[i]] = i;
    FOR(i,1,n) f[i] = f[p[a[i]-1]]+1;
    FOR(i,1,n) if(f[i] > f[res]) res = i;
    int l = a[res]-f[res]+1,r = a[res];
    printf("%d\n",n-f[res]);int t=l;
    FOR(i,1,n){
        if(a[i] >= l && a[i] <= r) t = a[i];
        else{
            if(a[i] < t) mark[a[i]] = 1;
            else mark[a[i]] = 2;
        }
    }
    ROF(i,n,1) if(mark[i] == 1) printf("%d 0\n",i);
    FOR(i,1,n) if(mark[i] == 2) printf("%d 1\n",i);
    return 0;
}
