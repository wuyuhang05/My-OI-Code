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

const int MAXN = 1000+5;
std::string str;
int m,n,a[MAXN*2],f[20][MAXN*2],Log[MAXN*2];

inline int Min(int x,int y){
    return a[x] <= a[y] ? x : y;
}

inline void pre(){
    FOR(i,0,n-1) f[0][i] = i;
    FOR(i,1,Log[n]){
        FOR(j,0,n-1){
            if(j+(1<<(i-1)) <= n) f[i][j] = Min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
        }
    }
}

inline int calc(int l,int r){
    int c = Log[r-l+1];
    return Min(f[c][l],f[c][r-(1<<c)+1]);
}

int main(){
    Log[0] = -1;FOR(i,1,2000) Log[i] = Log[i>>1]+1;
    std::ios::sync_with_stdio(false);
    while(std::cin >> str >> m){
        n = str.length();CLR(f,0);
        FOR(i,0,n-1) a[i] = str[i]-'0';
        pre();
        int pos = 0;std::vector<int> ans;m = n-m;
        while(m--){
            pos = calc(pos,n-m-1);
            ans.pb(a[pos++]);
        }
        pos = 0;
        for(pos = 0;pos < ans.size();++pos)
            if(ans[pos] != 0) break;
        if(pos == ans.size()) puts("0");
        else{
            FOR(i,pos,(int)ans.size()-1) printf("%d",ans[i]);
            puts("");
        }
    }
    return 0;
}
