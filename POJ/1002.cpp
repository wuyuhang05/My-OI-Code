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

LL hash(char *str){
    LL res = 0ll;
    int len = strlen(str+1);
    for(int i = 1,k = 1;k <= 7;i++){
        if(isdigit(str[i])){
            res *= 10ll;
            k++;
            res += str[i]-'0';
        }
        else if(str[i] >= 'A' && str[i] <= 'Z'){
            res *= 10ll;
            k++;
            res += ((str[i] - 'A' - (str[i] > 'Q'))/3+2);
        }
    }
    //DEBUG(res);
    return res;
}

const int MAXN = 100000+5;
char str[MAXN];
std::map<LL,int> S;

int main(){
    int N;scanf("%d",&N);
    FOR(i,1,N){
        scanf("%s",str+1);
        S[hash(str)]++;
    }
    bool flag = false;
    for(std::map<LL,int>::iterator it = S.begin();it != S.end();++it){
        if(it->second <= 1) continue;flag = true;
        //DEBUG(it->first);
        printf("%03d-%04d %d\n",it->first/10000,it->first%10000,it->second);
    }
    if(!flag) puts("No duplicates.");
    return 0;
}