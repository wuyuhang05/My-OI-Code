/*
USER: wuyuhan5
PROG: combo
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

int N,a1,a2,b1,b2,c1,c2;


int a[4],b[4];

int main(){
    freopen("combo.in","r",stdin);
    freopen("combo.out","w",stdout);
    int ans = 1;
    scanf("%d",&N);
    scanf("%d%d%d%d%d%d",&a[1],&a[2],&a[3],&b[1],&b[2],&b[3]);
    if(N < 5) {printf("%d\n",N*N*N);return 0;}
    for(int i = 1;i <= 3;i++){
        if(a[i] > b[i]) std::swap(a[i],b[i]);
        int dist = std::min(b[i] - a[i],a[i] + N - b[i]);
        if(dist < 5) ans *= 5 - dist;
        else ans = 0;
    }
    printf("%d\n",250 - ans);
    return 0;
}
