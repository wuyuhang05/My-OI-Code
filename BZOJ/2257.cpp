/*
 * Author: RainAir
 * Time: 2019-07-18 18:30:52
 */
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
std::map<int,int> S;
int n,k,a[MAXN];

inline void calc(int x){
    int q = std::sqrt(1.0*x);
    FOR(i,1,q){
        if(!(x%i)){
            if(i*i == x) S[i]++;
            else S[i]++,S[x/i]++;
        }
    }
}

int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",a+i),calc(a[i]);int ans = 1;
    for(std::map<int,int>::iterator it = S.begin();it != S.end();++it){
        if(it->se >= k) ans = std::max(ans,it->fi);
    }
    printf("%d\n",ans);
    return 0;
}
