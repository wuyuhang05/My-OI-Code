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

const int MAXN = 200000+5;
char str[MAXN];
std::stack<int> S;
int n,ps,ans;

int main(){
    scanf("%s",str+1);
    n = strlen(str+1);
    FOR(i,1,n){
        if(str[i] == '*') ps = i;
    }
    FOR(i,1,n){
        if(str[i] == '*') continue;
        if(str[i] == '(') S.push(i);
        else{
            if(S.empty()) continue;
            int v = S.top();S.pop();
            if(v < ps && i > ps) ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
