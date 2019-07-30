/*
 * Author: RainAir
 * Time: 2019-07-17 08:32:56
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

const int MAXN = 20+5;
int a[MAXN],b[MAXN];

int main(){
    FOR(i,1,7) scanf("%d",a+i);
    FOR(i,1,7) scanf("%d",b+i);
    std::sort(a+1,a+5+1);
    std::sort(b+1,b+5+1);
    if(a[6] > a[7]) std::swap(a[6],a[7]);
    if(b[6] > b[7]) std::swap(b[6],b[7]);
    int cnt1 = 0;
    FOR(i,1,5){
        FOR(j,1,5) if(a[i] == b[j]) {cnt1++;break;}
    }
    int cnt2 = 0;
    FOR(i,6,7) FOR(j,6,7) if(a[i] == b[j]) {cnt2++;break;};
    if(cnt1 == 5 && cnt2 == 2){
        puts("5000000");return 0;
    }
    if(cnt1 == 5 && cnt2 == 1){
        puts("250000");return 0;
    }
    if(cnt1 == 5 && !cnt2){
        puts("3000");return 0;
    }
    if(cnt1 == 4 && cnt2 == 2){
        puts("3000");return 0;
    }
    if(cnt1 == 4 && cnt2 == 1){
        puts("200");return 0;
    }
    if(cnt1 == 3 && cnt2 == 2){
        puts("200");return 0;
    }
    if((cnt1 == 4 && !cnt2) || (cnt1 == 3 && cnt2 == 1) || (cnt1 == 2 && cnt2 == 2)){
        puts("10");return 0;
    }
    if((cnt1 == 3 && !cnt2) || (cnt1 == 1 && cnt2 == 2) || (cnt1 == 2 && cnt2 == 1) || (!cnt1 && cnt2 == 2)){
        puts("5");return 0;
    }
    puts("0");
    return 0;
}

