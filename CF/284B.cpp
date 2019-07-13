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

const int MAXN = 2e5 + 5;
char str[MAXN];
int n;
int a,b,c;
int main(){scanf("%d",&n);
    scanf("%s",str+1);
    FOR(i,1,n){
        if(str[i] == 'A')a++;
        if(str[i] == 'F')b++;
        if(str[i] == 'I')c++;
    }
    if(c > 1){
        puts("0");return 0;
    }
    if(c == 1){
        puts("1");return 0;
    }
    printf("%d\n",a);
    return 0;
}
