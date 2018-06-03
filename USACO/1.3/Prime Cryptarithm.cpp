/*
ID: wuyuhan5
PROG: crypt1
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

bool hash[10];
int N;

bool check(int x){
    while(x){
        if(!hash[x%10]) return false;
        x /= 10;
    }
    return true;
}

int main(){
    freopen("crypt1.in","r",stdin);
    freopen("crypt1.out","w",stdout);
    scanf("%d",&N);
    for(int x,i = 1;i <= N;i++){
        scanf("%d",&x);
        hash[x] = true;
    }
    int ans = 0;
    for(int i = 100;i <= 999;i++){
        if(!check(i)) continue;
        for(int j = 10;j <= 99;j++){
            if(!check(j)) continue;
            int fa = i * (j % 10);
            if(fa > 999 || !check(fa)) continue;
            int fb = i * (j / 10);
            if(fb > 999 || !check(fb)) continue;
            int fc = i * j;
            if(fc > 9999 || !check(fc)) continue;
            ans++;
        }
    }
    printf("%d\n",ans);
    getchar();getchar();
    return 0;
}
