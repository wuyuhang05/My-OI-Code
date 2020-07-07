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
#include<bits/stdc++.h>
std::mt19937 g(time(NULL));

inline int gen(){
    return -1000000000+g()%2000000000;
}

int main(){
    freopen("a.in","w",stdout);
    int T=1;printf("%d\n",T);
    FOR(i,1,T){
        int n = 5000,m = 2000;
        printf("%d %d\n",n,m);
        FOR(i,1,n) printf("%d %d\n",gen(),gen());
        FOR(i,1,m) printf("%d %d\n",gen(),gen());
    }
    return 0;
}
