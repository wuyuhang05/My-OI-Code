/*
 * Author: RainAir
 * Time: 2020-03-03 15:35:38
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
int n;
int H[MAXN],sa[MAXN];

struct SA{
    int tp[MAXN],rk[MAXN],tax[MAXN];
    int M = 26,n;

    inline void sort(){
        FOR(i,0,M) tax[i] = 0;
        FOR(i,1,n) tax[rk[i]]++;
        FOR(i,1,M) tax[i] += tax[i-1];
        ROF(i,n,1) sa[tax[rk[tp[i]]]--] = tp[i];
    }

    inline void getH(){
        int j = 0;
        FOR(i,1,n){
            if(j) --j;
            while(str[i+j] == str[sa[rk[i]-1]+j]) ++j;
            H[rk[i]] = j;
        }
    }

    inline void build(){
        M = 30;FOR(i,1,n) rk[i] = str[i]-'a'+1,tp[i] = i;
        sort();
        for(int w=1,p=0;p < n;w <<= 1,M = p){
            p = 0;
            FOR(i,1,w) tp[++p] = n-w+i;
            FOR(i,1,n) if(sa[i] > w) tp[++p] = sa[i]-w;
            sort();
            std::swap(rk,tp);
            rk[sa[1]] = p = 1;
            FOR(i,2,n) rk[sa[i]] = tp[sa[i]] == tp[sa[i-1]] && tp[sa[i]+w] == tp[sa[i-1]+w] ? p : ++p;
        }
        getH();
    }
}_;

int N;
LL ans = 0;
int st[MAXN],tp,sm[MAXN],num[MAXN];

inline bool cmp(int x,int y){
    return H[x] < H[y];
}

inline void work(bool flag){
    tp = 0;sm[0] = num[0] = 0;
    FOR(i,1,n){
        if((sa[i] <= N)^(flag)){
            int t = 0;
            while(tp && H[st[tp]] >= H[i]) t += num[tp]-num[tp-1],--tp;
            st[++tp] = i;num[tp] = num[tp-1]+t+1;
            sm[tp] = sm[tp-1]+(t+1)*H[i];
        }
        else{
            if(sa[i] != N+1) ans += sm[tp];//,DEBUG(sm[tp]);
            int t = 0;
            while(tp && H[st[tp]] >= H[i]) t += num[tp]-num[tp-1],--tp;
            st[++tp] = i;num[tp] = num[tp-1]+t;sm[tp] = sm[tp-1]+t*H[i];
        }
    }
}

char tt[MAXN];

int main(){
    scanf("%s",str+1);N = n = strlen(str+1);str[++n] = '{';
    scanf("%s",tt+1);FOR(i,1,N) str[++n] = tt[i];_.n = n;
    _.build();
  //  FOR(i,1,n) DEBUG(H[i]);
    std::reverse(H+1,H+n+1);std::reverse(sa+1,sa+n+1);
    work(0);work(1);
    printf("%lld\n",ans);
    return 0;
}
