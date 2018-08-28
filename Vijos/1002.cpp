#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 1100000;
const int MAXM = 105;
const int ha = 100;

int stone[MAXM],a[MAXN],f[MAXN];
int L,M,s,t;

int main(){
    scanf("%d%d%d%d",&L,&s,&t,&M);
    for(int i = 1;i <= M;i++)
        scanf("%d",&stone[i]);
    if(s == t){
        int cnt = 0;
        for(int i = 1;i <= M;i++)
            if(stone[i] % s == 0)
                cnt++;
        printf("%d",cnt);
        return 0;
    }
    std::sort(stone + 1,stone + M + 1);
    for(int i = 1;i <= M;i++){
        int dist = stone[i] - stone[i-1];
        stone[i] = stone[i-1] + dist % ha;
    }
    L = (L - stone[M]) % ha + stone[M];
    for(int i = 1;i <= M;i++)
        a[stone[i]] = 1;
    memset(f,0x3f,sizeof(f));
    f[0] = 0;
    for(int i = s;i <= L + t;i++){
        for(int j = s;j <= t;j++)
            if(i >= j)
                f[i] = std::min(f[i],f[i-j] + a[i]);
    }
    int ans = (1 << 30) - 1;
    for(int i = L;i <= L + t;i++)
        ans = std::min(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}
