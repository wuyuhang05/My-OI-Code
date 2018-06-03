/*
https://vijos.org/d/SUOI/p/5a053aefd3d8a10a532dc137
O(n^2)超时做法
#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 10000000 + 5;

int a[MAXN],f[MAXN],N,ans;

int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;++i)
        scanf("%d",&a[i]);
    for(int i = 1;i <= N;i++){
        f[i] = 1;
        for(int j = 1;j < i;j++){
            if(a[i] > a[j])
                f[i] = std::max(f[i],f[j] + 1);
        }
        ans = std::max(ans,f[i]);
    }
    printf("%d\n",ans);
    getchar();getchar();
    return 0;
}
*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 10000000 + 5;

int N,a[MAXN],f[MAXN];

int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++)
        scanf("%d",&a[i]);
    f[1] = a[1];
    int ans = 1;
    for(int i = 2;i <= N;i++){
        if(a[i] > f[ans])
            f[++ans] = a[i];
        else{
            int j = std::lower_bound(f + 1,f + ans + 1,a[i]) - f;
            f[j] = a[i];
        }
    }
    printf("%d",ans);
    return 0;
}
