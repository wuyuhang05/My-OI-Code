#include <iostream>
#include <cstring>
#include <cstdio>

#define lowbit(x) x & -x
#define LL long long

const int MAXN = 500000 + 5;

int N,M;

struct BIT{
    LL tree[MAXN];

    inline void add(LL x,LL k){
        while(x <= N){
            tree[x] += k;
            x += lowbit(x);
        }
    }

    inline void modify(int l,int r,LL delta){
        add(l,delta);
        add(r+1,-delta);
    }

    inline LL sum(int x){
        LL ans = 0;
        while(x){
            ans += tree[x];
            x -= lowbit(x);
        }
        return ans;
    }
}bit;
int main(){
    scanf("%d%d",&N,&M);
    LL last = 0;
    for(int x,i = 1;i <= N;i++){
        scanf("%d",&x);
        bit.add(i,x-last);
        last = x;
    }
    for(int i = 1;i <= M;i++){
        LL d;
        scanf("%lld",&d);
        if(d & 1){
            LL x,y,k;
            scanf("%lld%lld%lld",&x,&y,&k);
            bit.modify(x,y,k);
        }
        else{
            LL x,y;
            scanf("%lld%lld",&x);
            printf("%lld\n",bit.sum(x));
        }
    }
    //getchar();getchar();getchar();
    return 0;
}
