/*
 * Author: RainAir
 * Time: 2019-08-26 11:12:27
 */
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
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e6 + 5;
const int BASE = 131;
char str[MAXN];
int n;
U LL hash[MAXN],b[MAXN],anss;
bool flag = false;
std::vector<char> ans;

int main(){
    scanf("%d",&n);
    scanf("%s",str+1);
    if(!(n&1)){
        puts("NOT POSSIBLE");return 0;
    }
    b[0] = 1;
    FOR(i,1,n) hash[i] = hash[i-1]*BASE+(str[i]-'A'+1),b[i] = b[i-1]*BASE;
    if(hash[n/2] == hash[n]-hash[n/2+1]*b[n/2]){
        flag = true;
        FOR(i,1,n/2) ans.pb(str[i]);
        anss = hash[n/2];
    }
    int mid = n/2+1;
    FOR(i,1,n/2){
        U LL lh = hash[mid]-hash[i]*b[mid-i]+hash[i-1]*b[n/2-i+1],rh = hash[n]-hash[mid]*b[n/2];
        if(lh == rh){
            if(flag){
                if(anss != lh)
                    {puts("NOT UNIQUE");return 0;}
            }
            else{
                flag = true;
                FOR(i,mid+1,n) ans.pb(str[i]);
                anss = lh;
            }
        }
    }
    FOR(i,n/2+2,n){
        U LL lh = hash[mid-1],rh = hash[n]-hash[i]*b[n-i]+(hash[i-1]-hash[n/2]*b[i-1-n/2])*b[n-i];
        if(lh == rh){
            if(flag){
                if(anss != lh){
                puts("NOT UNIQUE");return 0;
            }}
            else{
                flag = true;
                FOR(i,1,mid-1) ans.pb(str[i]);
                anss = lh;
            }
        }
    }
    if(!flag){
        puts("NOT POSSIBLE");return 0;
    }
    FOR(i,0,(int)ans.size()-1) putchar(ans[i]);puts("");
    return 0;
}
