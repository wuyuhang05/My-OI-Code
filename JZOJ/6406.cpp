/*
 * Author: RainAir
 * Time: 2019-11-05 15:45:08
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
std::set<P> S;

int main(){
    freopen("problem.in","r",stdin);
    freopen("problem.out","w",stdout);
    int n;scanf("%d",&n);--n;
    FOR(x,0,n-1){
        FOR(i,0,n-1){
            int j = (x-i+n)%n;
            if(i != j) S.insert(MP(std::min(i,j),std::max(i,j)));
            else S.insert(MP(i,n));//,DEBUG(n);
        }
        for(auto x:S){
            printf("%d %d ",x.fi+1,x.se+1);
        }
        puts("");S.clear();
    }
    return 0;
}
