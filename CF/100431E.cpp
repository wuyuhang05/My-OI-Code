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

const int MAXN = 4e5 + 5;
char str[MAXN];
int nxt[MAXN],rlim[MAXN],ans[MAXN];
int n;

int main(){
    scanf("%s",str+1);n = strlen(str+1);
    FOR(i,2,n){
        int j = nxt[i-1];
        while(j && str[j+1] != str[i]) j = nxt[j];
        if(str[j+1] == str[i]) nxt[i] = j+1;
        else nxt[i] = 0;
    }
    FOR(i,1,n){
        if(nxt[i] == 0){
            ans[i] = rlim[i] = i;
        }
        else{
            if(ans[nxt[i]]+rlim[ans[nxt[i]]] >= i){
                ans[i] = ans[nxt[i]];
                rlim[ans[i]] = i;
            }
            else{
                ans[i] = rlim[i] = i;
            }
        }
        printf("%d ",ans[i]);
    }
    puts("");
    return 0;
}
