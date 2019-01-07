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

const int MAXN = 20+1;
int N,C;
int base[MAXN];
int a[MAXN],b[MAXN];
int f[(1<<MAXN)+1];

inline int pd(){

}

int main(){
    base[0] = 1;FOR(i,1,MAXN-1) base[i] = base[i-1]<<1;
    scanf("%d%d",&N,&C);
    FOR(i,1,N) scanf("%d%d",a+i,b+i);
    CLR(f,0x7f);f[0] = 0;
    FOR(S,1,(1<<N)-1){
        bool flag = false;
        std::vector<int> v;
        FOR(i,1,N){ // 枚举每一个元素
            if((1<<i-1) & S){
                if(std::abs(a[i]-b[i]) > C) flag = 1;
                v.push_back(a[i]),v.push_back(b[i]);
            }
        }
        FOR(i,0,(int)v.size()-1) printf("%d ",v[i]);
        if(!flag) f[S] = 0;
        else{
            std::sort(v.begin(),v.end());
            flag = false;
            for(int j = 1;j < v.size();j += 2){
                DEBUG(v[j]);DEBUG(v[j-1]);
                if(v[j] - v[j-1] > C){
                    flag = true;
                    break;
                }
            }
            if(!flag) f[S] = ((int)v.size()>>1)-1;
        }
        DEBUG(S);DEBUG(f[S]);
    }
    FOR(S,1,(1<<N)-1){
        for(int i = (S-1)&S;i;i = (i-1)&S){
            f[S] = std::min(f[S],f[i]+f[i^S]);
        }
    }
    printf("%d\n",f[(1<<N)-1] == INT_MAX ? -1 : f[(1<<N)-1]);
    return 0;
}