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

const int MAXN = 1e6 + 5;

char str[MAXN];
std::deque<char> q;
int n,m,rev,now;

int main(){
    scanf("%d%d",&n,&m);
    int T;scanf("%d",&T);
    scanf("%s",str+1);
    FOR(i,1,m) q.pb(str[i]);now = 1;
    while(T--){
        int opt,x;scanf("%d%d",&opt,&x);
        if(opt == 1){
            while(now < x){
                if(rev) str[now] = q.back(),q.pop_back(),q.push_front(str[now+m]);
                else str[now] = q.front(),q.pop_front(),q.pb(str[now+m]);
                now++;
            }
            rev^=1;
        }
        else{
            if(x < now) putchar(str[x]);
            else if(x > now+m-1) putchar(str[x]);
            else putchar(q[!rev?x-now:m-(x-now)-1]);
        }
    }
    return 0;
}
/*
5 1 5
abcde
2 1
1 1
2 1
1 4
2 5
*/

