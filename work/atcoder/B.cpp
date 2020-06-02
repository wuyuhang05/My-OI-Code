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

const int MAXN = 5e5 + 5;
char str[MAXN];int n;
int f[MAXN][2];

int main(){
    scanf("%s",str+1);n = strlen(str+1);
    f[0][0] = 0;f[0][1] = -1e9;// 0:D 1:P
    FOR(i,1,n){
        if(str[i] == 'P'){
            f[i][1] = std::max(f[i-1][0],f[i-1][1]);
            f[i][0] = -1e9;
        }
        else if(str[i] == 'D'){
            f[i][1] = -1e9;
            f[i][0] = std::max(f[i-1][0],f[i-1][1]+1)+1;
        }
        else{
            f[i][1] = std::max(f[i-1][0],f[i-1][1]);
            f[i][0] = std::max(f[i-1][0],f[i-1][1]+1)+1;
        }
    }
    int now = f[n][0] > f[n][1] ? 0 : 1;std::vector<char> ans;
    ROF(i,n,1){
        if(now == 0){
            ans.pb('D');
            if(f[i-1][0]+1 == f[i][0]) now = 0;
            else now = 1;
        }
        else{
            ans.pb('P');
            if(f[i-1][0] == f[i][1]) now = 0;
            else now = 1;
        }
    }
    std::reverse(all(ans));
    for(auto x:ans) putchar(x);
    return 0;
}
