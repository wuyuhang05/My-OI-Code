/*
 * Author: RainAir
 * Time: 2019-09-24 15:00:43
 */
#include <algorithm>
#include <iostream>
#include <assert.h>
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;

char s1[MAXN],s2[MAXN];
int pre[MAXN],suf[MAXN];
char _pre[MAXN],_suf[MAXN];
int n,m;

inline void Solve(){
    scanf("%s%s",s1+1,s2+1);
    n = strlen(s1+1);m = strlen(s2+1);
    bool flag = true;int cnt1 = 0,cnt2 = 0;
    FOR(i,1,n) flag &= s1[i] != '*',cnt1 += (s1[i] != '*');
    FOR(i,1,m) flag &= s2[i] != '*',cnt2 += (s2[i] != '*');
    if(flag && n == m){
        FOR(i,1,n) putchar(s1[i] == s2[i] ? s1[i] : '?');
        puts("");
        return;
    }
    int len = std::min(cnt1,cnt2)+1;flag = false;
    FOR(i,1,len){
        flag |= (s1[i] == '*' || s2[i] == '*');
        if(flag){
            pre[i] = pre[i-1] + 1;_pre[i] = '?';
        }
        else{
            if(s1[i] == s2[i] && s1[i] != '?') pre[i] = pre[i-1],_pre[i] = s1[i];
            else pre[i] = pre[i-1]+1,_pre[i] = '?';
        }
    }
    flag = false;
    ROF(i,len,1){ // suf[i]
        int t = len-i;
        flag |= (s1[n-t] == '*' || s2[m-t] == '*');
        if(flag){
            suf[i] = suf[i+1] + 1;_suf[i] = '?';
        }
        else{
            if(s1[n-t] == s2[m-t] && s1[n-t] != '?') suf[i] = suf[i+1],_suf[i] = s1[n-t];
            else suf[i] = suf[i+1]+1,_suf[i] = '?';
        }
    }
    int ps = -1,mn = 1e9;
    FOR(i,1,len){
        if(mn > pre[i-1]+suf[i+1]){
            mn = pre[i-1]+suf[i+1];
            ps = i;
        }
    }
    assert(ps != -1);
    FOR(i,1,ps-1) putchar(_pre[i]);
    putchar('*');
    FOR(i,ps+1,len) putchar(_suf[i]);
    puts("");
    CLR(pre,0);CLR(suf,0);CLR(_pre,0);CLR(_suf,0);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
