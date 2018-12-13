#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 20000+5;

struct BigInt{
    #define int_2048 BigInt
    #define SIZE 2048
    int len,a[SIZE];

    BigInt(){
        len=1;CLR(a,0);
    }

    inline void print(char ch){
        ROF(i,len,1) printf("%d",a[i]);
        putchar(ch);
    }

    BigInt operator + (const BigInt &b) const {
        BigInt ans;
        ans.len = std::max(len,b.len);
        FOR(i,1,ans.len){
            ans.a[i] += a[i] + b.a[i];
            ans.a[i+1] += (ans.a[i] >> 1);
            ans.a[i] &= 1;
        }
        if(ans.a[ans.len+1]) ans.len++;
        return ans;
    }

    BigInt operator * (const int &b) const {
        BigInt ans = (*this);
        FOR(i,1,ans.len) ans.a[i] *= b;
        FOR(i,1,ans.len){
            ans.a[i+1] += (ans.a[i] >> 1);
            ans.a[i] &= 1;
        }
        while(ans.a[ans.len+1]){
            ans.len++;
            ans.a[ans.len+1] += ans.a[ans.len]>>1;
            ans.a[ans.len] &= 1;
        }
        return ans;
    }
    #undef SIZE
};

int_2048 k,v,q[MAXN],f[MAXN];

int main(){
    int N;scanf("%d",&N);
    k.a[1] = v.a[1] = 1;q[1].a[1] = f[1].a[1] = 0;
    int l=1,r=1,t=1,cnt=0,tot=1;
    for(;;l=r+1,r=tot,++t){
        FOR(i,l,r){
            if(!q[i].a[t]) q[++tot] = q[i],f[tot] = f[i];
        }
        FOR(i,l,r){
            if(!q[i].a[t]){
                q[++tot] = q[i]+k;f[tot] = f[i]+v;cnt++;
                if(cnt == N){
                    f[tot].print('\n');
                    return 0;
                }
            }
        }
        v = v*2;k = k*10;
    }
    return 0;
}