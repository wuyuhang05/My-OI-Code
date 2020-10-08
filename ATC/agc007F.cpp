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

const int MAXN = 2e6 + 5;
char S[MAXN],T[MAXN];
int n;std::queue<int> q;

int main(){
    scanf("%d",&n);
    scanf("%s",S+1);scanf("%s",T+1);
    bool flag = 1;
    FOR(i,1,n) flag &= (S[i]==T[i]);
    if(flag){
        puts("0");
        return 0;
    }
    int up = n,down = n;
    int tag = 0,ans = 0;
    while(down){
        while(down && T[down-1] == T[down]) down--;
        while(up && (up > down || S[up] != T[down])) up--;
        if(up == 0){
            puts("-1");
            return 0;
        }
        while(!q.empty() && q.front()+tag >= down) q.pop();
        if(up != down) q.push(up-tag);
        ans = std::max(ans,(int)q.size()+1);
        tag--;--down;
    }
    printf("%d\n",ans);
    return 0;
}
