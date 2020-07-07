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

const int MAXN = 1e4+5;
char str[MAXN];
int f[2][MAXN];
int n,ha;

inline void add(int &x,int y){
    (x += y);if(x >= ha) x -= ha;
}

int main(){
    char ch = getchar();
    while(ch != '\n') str[++n] = ch,ch = getchar();
    scanf("%d",&ha);int now=0;
    FOR(i,0,n) f[now][i] = 1;
    FOR(i,1,n){
        now ^= 1;CLR(f[now],0);f[now][0] = 1;
        FOR(j,1,n){
            if(str[i] == str[j]) f[now][j] = f[now^1][j-1];
            else f[now][j] = 0;
            add(f[now][j],f[now^1][j]);add(f[now][j],f[now][j-1]);
            add(f[now][j],ha-f[now^1][j-1]);
        }
    }
    printf("%d\n",f[now][n]);
    return 0;
}
