#include<bits/stdc++.h>

#define fi first
#define se second
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
std::mt19937 g(time(NULL));
inline void Solve(){
    printf("%d %d %d\n",50000,200000,2);
    FOR(i,1,50000) putchar('a'+g()%26);
    puts("");
    FOR(i,1,200000){
        if(g()%2 == 1){
            puts("2");
        }
        else printf("1 %c\n",'a'+g()%26);
    }
}

int main(){
        freopen("a.in","w",stdout);
        FOR(i,1,5) Solve();
        return 0;
}
