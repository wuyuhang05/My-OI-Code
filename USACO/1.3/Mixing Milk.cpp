/*
ID: wuyuhan5
PROG: milk
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5000 + 5;

int N,M;
std::pair<int,int> data[MAXN];

int main(){
    freopen("milk.in","r",stdin);
    freopen("milk.out","w",stdout);
    scanf("%d%d",&N,&M);
    for(int i = 1;i <= M;i++)
        scanf("%d%d",&data[i].first,&data[i].second);
    std::sort(data + 1,data + M + 1);
    int ans = 0;
    for(int i = 1;i <= M;i++){
        if(data[i].second >= N){
            ans += data[i].first * N;
            break;
        }
        ans += data[i].second * data[i].first;
        N -= data[i].second;
    }
    printf("%d\n",ans);
    getchar();getchar();
    return 0;
}
