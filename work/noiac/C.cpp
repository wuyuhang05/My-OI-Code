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

const int MAXN = 2e6 + 5;

int k,n,m;
int x[MAXN],mx[MAXN];
int st[MAXN],tp;
bool ins[MAXN];

int main(){
    scanf("%d%d",&m,&k);
    FOR(i,1,m){
        int t;scanf("%d",&t);
        if(t <= k) x[++n] = t,mx[t] = n;
    }
    st[tp = 1] = x[1];ins[x[1]] = 1;
    FOR(i,2,n){
        if(ins[x[i]]) continue;
        while(tp && st[tp] > x[i] && mx[st[tp]] > i) ins[st[tp]] = 0,tp--;
        st[++tp] = x[i];ins[x[i]] = 1;
    }
    FOR(i,1,tp) printf("%d ",st[i]);
    return 0;
}
