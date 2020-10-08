#include <bits/stdc++.h>

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

const int MAXN = 1e5 + 5;
char str[MAXN];

int main(){
    int T;scanf("%d",&T);
    while(T--){
        scanf("%s",str+1);int len = strlen(str+1);
        int o;scanf("%d",&o);
        int x = str[len]-'0';
        if(len == 1){
            if(x == 2){
                printf("%d\n",o);
            }
            else if(x == 3){
                printf("%d\n",o);
            }
            else{
                printf("%d\n",o|(!(x&1)));
            }
        }
        else{
            int x = str[len]-'0';
            printf("%d\n",o|(!(x&1)));
        }
    }
    return 0;
}