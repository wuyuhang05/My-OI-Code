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
#define int LL
const int MAXN = 14+2;
const int MAXM = 4782969+233;
int pw[MAXN],trans[MAXM];
int f[MAXM],n;
//0: 没打 1: 打了没拿宝石 2: 打了
int H[MAXN],A[MAXN],D[MAXN],S[MAXN];
int ap[MAXN],dp[MAXN],mp[MAXN],hp[MAXN];
int todo[MAXN];

inline void Solve(){
    int sh,sa,sd,sm;
    scanf("%lld%lld%lld%lld",&sh,&sa,&sd,&sm);
    scanf("%lld",&n);CLR(todo,0);
    FOR(i,0,n-1){
        scanf("%lld%lld%lld%lld%lld%lld%lld%lld",H+i,A+i,D+i,S+i,ap+i,dp+i,mp+i,hp+i);
    }
    CLR(f,-1);
    f[0] = sh;
    int k;scanf("%lld",&k);
    FOR(i,1,k){
        int u,v;scanf("%lld%lld",&u,&v);--u;--v;
        todo[v] |= (1<<u);
    }
    FOR(S,0,pw[n]-1){
        if(f[S] == -1) continue;
  //      DEBUG(S);DEBUG(f[S]);
        int _h=f[S],_a=sa,_d=sd,_m=sm;
        int tt = 0;
        FOR(i,0,n-1){
            if((S/pw[i])%3) tt |= (1<<i);
            if((S/pw[i])%3 == 2){
                _a += ap[i];
                _d += dp[i];
                _m += mp[i];
            }
        }
        assert(tt==trans[S]);
        FOR(i,0,n-1){
            if((S/pw[i])%3 == 2) continue;
            if((S/pw[i])%3 == 1){
                int nxt = S+pw[i];
                f[nxt] = std::max(f[nxt],f[S]+hp[i]);
            }
            else{
                if((todo[i]&trans[S]) != todo[i]) continue;
                int h=_h,a=_a,d=_d,m=_m;
                int nxt = S+pw[i];
                int th=H[i],ta=A[i],td = D[i];
                int ss = 0;
                if(::S[i]&8) th = h,ta = a,td = d;
                if(::S[i]&2) d = 0;
                if(a <= td) continue;
                if(ta <= d){
                    f[nxt] = std::max(f[nxt],h);
                    continue;
                }
                ta -= d;
                if(::S[i]&4) ta *= 2;
                if(::S[i]&1) ss += ta;
                int t = th/(a-td);
                if(th%(a-td) == 0) t--;
                ss += t*ta;
                ss = std::max(0ll,ss-m);
                h -= ss;
                if(h > 0) f[nxt] = std::max(f[nxt],h);
            }
        }
    }
//    DEBUG(pw[n]-1);
    printf("%lld\n",f[pw[n]-1]<=0?-1:f[pw[n]-1]);
}

signed main(){
    pw[0] = 1;
    FOR(i,1,MAXN-1) pw[i] = 3*pw[i-1];
    FOR(i,1,MAXM-1){
        trans[i] = (trans[i/3]<<1)|((bool)(i%3));
    }
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}
