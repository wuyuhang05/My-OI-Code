/*
 USER: wuyuhan5
 LANG: C++
 PROB: skidesign
*/
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#define LL long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000 + 5;
const int DELTA = 17;

int N,a[MAXN];
LL ans;
int L,R;

int main(){
    freopen("skidesign.in","r",stdin);
    freopen("skidesign.out","w",stdout);
    scanf("%d",&N);
    R = INT_MIN;L = INT_MAX;
    ans = LLONG_MAX;
    for(int i = 1;i <= N;i++){
        scanf("%d",a+i);
        L = std::min(a[i],L);
        R = std::max(R,a[i]);
    }
    for(int d = L;d <= R;d++){
        LL tot = 0;
        for(int i = 1;i <= N;i++){
            if(a[i]-d > 17) tot += (a[i]-d-17)*(a[i]-d-17);
            if(a[i] < d) tot += (d-a[i]) * (d-a[i]);
        }
        ans = std::min(ans,tot);
    }
    printf("%lld\n",ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}

