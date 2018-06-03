#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 100000 + 5;

int value[20 + 5],weight[20 + 5],f[MAXN];

int main(){
    int sum,N;
    while(~scanf("%d%d",&sum,&N)){
        for(int i = 1;i <= N;i++)
            scanf("%d%d",&value[i],&weight[i]);
        if(!sum || !N){
            printf("%d\n",0);
            continue;
        }
        memset(f,0,sizeof(f));
        f[0] = 1;
        int ans = 0;
        for(int i = 1;i <= N;i++){
            for(int j = ans;j >= 0;j--){
                if(f[j]){
                    for(int k = 1;k <= value[i];k++){
                        int t = j + k * weight[i];
                        if(t > sum)
                            continue;
                        f[t] = 1;
                        if(t > ans)
                            ans = t;
                    }
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
