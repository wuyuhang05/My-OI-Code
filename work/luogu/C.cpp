#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int main(){
    int n,cs;scanf("%d%d",&n,&cs);
    if(cs <= 2){
        if(n == 1){
            puts("1");
            std::fflush(stdout);
        }
        if(n == 2){
            puts("1");
            std::fflush(stdout);
            int p,t;scanf("%d%d",&p,&t);
            if(p == 1) p = 2;
            else p = 1;
            printf("%d %d\n",p,t);
            std::fflush(stdout);
        }
        if(n == 3){
            puts("1");std::fflush(stdout);
            int p,t;scanf("%d%d",&p,&t);
            if(p == 1){
                printf("%d %d\n",2,t);                std::fflush(stdout);

            }
            if(p == 2){
                printf("%d %d\n",3,t);                std::fflush(stdout);

            }
            if(p == 3){
                printf("%d %d\n",2,t);
                std::fflush(stdout);
            }
        }
        if(n == 4){
            puts("1");std::fflush(stdout);
            int p,t;scanf("%d%d",&p,&t);
            if(p == 1){
                printf("%d %d\n",4,t);
                std::fflush(stdout);
                scanf("%d%d",&p,&t);
                if(p == 2) printf("%d %d\n",3,t);
                else printf("%d %d\n",2,t);
                std::fflush(stdout);
            }
            else if(p == 2){
                printf("%d %d\n",3,t);
                std::fflush(stdout);
                scanf("%d%d",&p,&t);
                if(p == 1) printf("%d %d\n",4,t);
                else printf("%d %d\n",1,t);
                std::fflush(stdout);
            }
            else if(p == 3){
                printf("%d %d\n",2,t);
                std::fflush(stdout);
                scanf("%d%d",&p,&t);
                if(p == 1) printf("%d %d\n",4,t);
                else printf("%d %d\n",1,t);
                std::fflush(stdout);
            }
            else if(p == 4){
                printf("%d %d\n",1,t);
                std::fflush(stdout);
                scanf("%d%d",&p,&t);
                if(p == 2) printf("%d %d\n",3,t);
                else printf("%d %d\n",2,t);
                std::fflush(stdout);
            }
        }
        if(n > 4){

        }
    }
    if(cs == 3){
        puts("1");std::fflush(stdout);
        FOR(i,1,n/2){
            int p,t;scanf("%d%d",&p,&t);
            printf("%d %d\n",p+1,t);
            std::fflush(stdout);
        }
    }
    return 0;
}
