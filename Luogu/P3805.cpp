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

const int MAXN = 2e7 + 5;
char str[MAXN],a[MAXN<<1];
int p[MAXN<<1];
int n;

int main(){
    scanf("%s",str+1);int len = strlen(str+1);
    a[0] = '#';a[n = 1] = '$';
    FOR(i,1,len) a[++n] = str[i],a[++n] = '$';
    int mx=0,mid=0;
    FOR(i,1,n){
        if(mx > i) p[i] = std::min(p[2*mid-i],p[mid]-(i-mid));
        else p[i] = 1;
        while(a[i-p[i]] == a[i+p[i]]) p[i]++;
        if(i+p[i] > mx){
            mx = i+p[i];mid = i;
        }
    }
    int ans = 1;
    FOR(i,1,n) ans = std::max(ans,p[i]);
    printf("%d\n",ans-1);
    return 0;
}
