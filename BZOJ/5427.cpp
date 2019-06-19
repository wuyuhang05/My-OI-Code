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

const int MAXN = 100000+5;

int f[MAXN];

int main(){
    int n,tag=0,L=0,R=0;scanf("%d",&n);
    char str[23];
    f[0] = -1000000001;
    FOR(i,1,n){
        scanf("%s",str);
        if(str[0] == 'K'){
            int x;scanf("%d",&x);
            int l = L,r = R,t;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(f[mid]+tag < x) l = mid+1,t = mid;
                else r = mid-1;
            }
            if(t == R) f[t+1] = x - tag,++R;
            else f[t+1] = std::min(f[t+1],x-tag);
        }
        else{
            ++tag;
        }
    }
    printf("%d\n",tag+R);
    return 0;
}
