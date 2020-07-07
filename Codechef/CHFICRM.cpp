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

const int MAXN = 1000+5;
int a[MAXN];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);int cnt5 = 0,cnt10=0,cnt15 = 0;
        FOR(i,1,n) scanf("%d",a+i);bool flag = true;
        FOR(i,1,n){
            if(a[i] == 5) cnt5++;
            if(a[i] == 10){
                if(cnt5) cnt5--;
                else{
                    flag = 0;break;
                }
                cnt10++;
            }
            if(a[i] == 15){
                if(cnt10){
                    cnt10--;
                }
                else if(cnt5 >= 2){
                    cnt5 -= 2;
                }
                else {flag = 0;break;}
                cnt15++;
            }
        }
        puts(flag?"YES":"NO");
    }
    return 0;
}
