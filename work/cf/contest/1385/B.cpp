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

const int MAXN=1e5+5;
int a[MAXN];
bool vis[MAXN];
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        FOR(i,1,2*n) scanf("%d",a+i);
        FOR(i,1,n) vis[i] = 0;
        FOR(i,1,2*n){
            if(!vis[a[i]]) printf("%d ",a[i]),vis[a[i]] = 1;
        }
        puts("");
    }
    return 0;
}
