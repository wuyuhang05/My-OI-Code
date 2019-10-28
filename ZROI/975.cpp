/*
 * Author: RainAir
 * Time: 2019-10-27 11:08:51
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

const int MAXN = 500000+5;
std::map<P,int> V;
std::set<P> E;
char str[MAXN];int n;

int main(){
    scanf("%s",str+1);
    n = strlen(str+1);
    int x=0,y=0;
    V[MP(x,y)] = V.size();
    FOR(i,1,n){
        int u = V[MP(x,y)];
        if(str[i] == 'L') --x;
        if(str[i] == 'R') ++x;
        if(str[i] == 'U') ++y;
        if(str[i] == 'D') --y;
        if(!V.count(MP(x,y))) V[MP(x,y)] = V.size();
        int v = V[MP(x,y)];
        if(u > v) std::swap(u,v);
        E.insert(MP(u,v));
    }
    printf("%d\n",(int)((int)E.size()-(int)V.size()+2));
    return 0;
}
