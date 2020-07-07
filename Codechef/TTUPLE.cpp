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
int a[4],b[4];
int p[4];

inline int Solve(){
    FOR(i,1,3) scanf("%lld",a+i);FOR(i,1,3) scanf("%lld",b+i);
    if(a[1] == b[1] && a[2] == b[2] && a[3] == b[3]) return 0;
    int c0 = 0;
    std::vector<int> v;FOR(i,1,3) v.pb(b[i]-a[i]);
    for(auto x:v) if(x==0) c0++;
    std::sort(all(v));
    if(v[0]==v[1]&&v[1]==v[2]) return 1;
    if(c0 == 2) return 1;
    std::set<int> S;for(auto x:v) S.insert(x);
    if(c0 == 1&& S.size()==2) return 1;

    std::vector<int> vv;bool flag = true;
    FOR(i,1,3){
        if(a[i] == b[i]) continue;
        else if(a[i] == 0){flag = false;break;}
        int d = b[i]/a[i];
        if(d*a[i] != b[i]){flag = false;break;}
        vv.pb(d);
    }std::sort(all(vv));
    std::set<int> SS;for(auto x:vv) SS.insert(x);
    if(flag){
        if(vv.size() == 1) return 1;
        if(vv.size() == 2 && SS.size() == 1) return 1;
        if(vv.size() == 3 && SS.size() == 1) return 1;
    }

    if(c0 == 1) return 2;
    if(S.size() == 2) return 2;
    FOR(i,0,2) if(2*v[i] == v[0]+v[1]+v[2]) return 2;
    
    if(flag){
        if(vv.size() == 2) return 2;
        if(SS.size() == 2) return 2;
        if(vv[0]*vv[1] == vv[2]) return 2;
        if(vv[1]*vv[2] == vv[0]) return 2;
        if(vv[0]*vv[2] == vv[1]) return 2;
    }

    // *+
    FOR(S,0,(1<<3)-1){//*
        FOR(T,0,(1<<3)-1){//+
            if(S == T){
                if(S != (1<<3)-1) continue;
                if(a[1]-a[2] == 0) continue;
                int d1 = (b[1]-b[2])/(a[1]-a[2]);
                if((a[1]-a[2])*d1 != (b[1]-b[2])) continue;
                int d2 = b[1]-a[1]*d1;bool flag = true;
                FOR(i,1,3) flag &= (a[i]*d1+d2 == b[i]);
                if(flag) return 2;
                continue;
            }
            if((S&T) == 0) continue;
            if((S|T) != (1<<3)-1) continue;
            bool type = 0;int ps = -1;
            FOR(i,0,2){
                if(((S>>i)&1) && !((T>>i)&1)){
                    type = 0;ps = i+1;break;
                }
                if(!((S>>i)&1) && ((T>>i)&1)){
                    type = 1;ps = i+1;break;
                }
            }
            if(ps == -1) continue;
            if(type == 0){
                if(a[ps] == 0) continue;
                int d1 = b[ps]/a[ps];
                if(d1*a[ps] != b[ps]) continue;
                bool flag = 1;
                if(!T){
                    FOR(i,0,2){
                        if((S>>i)&1) flag &= (a[i+1]*d1==b[i+1]);
                        else flag &= (a[i+1]==b[i+1]);
                    }
                }
                else{
                    int d2=0;
                    FOR(i,0,2){
                        if(((S>>i)&1) && ((T>>i)&1)){
                            d2 = b[i+1]-a[i+1]*d1;
                            break;
                        }
                    }
                    FOR(i,0,2){
                        if(((S&T)>>i)&1) flag &= (a[i+1]*d1+d2==b[i+1]);
                        else if((S>>i)&1) flag &=  (a[i+1]*d1==b[i+1]);
                        else if((T>>i)&1) flag &= (a[i+1]+d2==b[i+1]);
                        else flag &= (a[i+1]==b[i+1]);
                    }
                }
                if(flag) return 2;
            }
            else{
                int d2 = b[ps]-a[ps];
                bool flag = 1;
                if(!S){
                    FOR(i,0,2){
                        if((T>>i)&1) flag &= (a[i+1]+d2==b[i+1]);
                    }
                }
                else{
                    int d1 = 0;
                    FOR(i,0,2){
                        if(((S>>i)&1) && ((T>>i)&1)){
                            if(a[i+1] == 0) {flag = 0;continue;}
                            int t = (b[i+1]-d2)/a[i+1];
                            if(t*a[i+1]+d2 != b[i+1]){flag = 0;continue;}
                            d1 = t;break;
                        }
                    }
                    FOR(i,0,2){
                        if(((S&T)>>i)&1) flag &= (a[i+1]*d1+d2==b[i+1]);
                        else if((S>>i)&1) flag &=  (a[i+1]*d1==b[i+1]);
                        else if((T>>i)&1) flag &= (a[i+1]+d2==b[i+1]);
                        else flag &= (a[i+1]==b[i+1]);
                    }
                }
                if(flag) return 2;
            }
        }
    }

    FOR(S,0,(1<<3)-1){//*
        FOR(T,0,(1<<3)-1){//+
            if(S == T){
                if(S != (1<<3)-1) continue;
                if(b[1]-b[2] == 0) continue;
                int d2 = (b[2]*a[1]+a[2]*b[1])/(b[1]-b[2]);
                if((b[1]-b[2])*d2 != b[2]*a[1]+a[2]*b[1]) continue;
                if(a[1]+d2 == 0) continue;
                int d1 = b[1]/(a[1]+d2);bool flag = 1;
                FOR(i,1,3) flag &= ((a[i]+d2)*d1 == b[i]);
                if(flag) return 2;
                continue;
            }
            if((S&T) == 0) continue;
            if((S|T) != (1<<3)-1) continue;
            bool type = 0;int ps = -1;
            FOR(i,0,2){
                if(((S>>i)&1) && !((T>>i)&1)){
                    type = 0;ps = i+1;break;
                }
                if(!((S>>i)&1) && ((T>>i)&1)){
                    type = 1;ps = i+1;break;
                }
            }
            if(ps == -1) continue;
            if(type == 0){
                if(a[ps] == 0) continue;
                int d1 = b[ps]/a[ps];
                if(d1*a[ps] != b[ps]) continue;
                bool flag = 1;
                if(!T){
                    FOR(i,0,2){
                        if((S>>i)&1) flag &= (a[i+1]*d1==b[i+1]);
                        else flag &= (a[i+1]==b[i+1]);
                    }
                }
                else{
                    int d2=0;
                    FOR(i,0,2){
                        if(((S>>i)&1) && ((T>>i)&1)){
                            if(d1 == 0){flag = 0;break;}
                            d2 = b[i+1]/d1-a[i+1];
                            break;
                        }
                    }
                    FOR(i,0,2){
                        if(((S&T)>>i)&1) flag &= ((a[i+1]+d2)*d1==b[i+1]);
                        else if((S>>i)&1) flag &=  (a[i+1]*d1==b[i+1]);
                        else if((T>>i)&1) flag &= (a[i+1]+d2==b[i+1]);
                        else flag &= (a[i+1]==b[i+1]);
                    }
                }
                if(flag) return 2;
            }
            else{
                int d2 = b[ps]-a[ps];
                bool flag = 1;
                if(!S){
                    FOR(i,0,2){
                        if((T>>i)&1) flag &= (a[i+1]+d2==b[i+1]);
                    }
                }
                else{
                    int d1 = 0;
                    FOR(i,0,2){
                        if(((S>>i)&1) && ((T>>i)&1)){
                            if(a[i+1]+d2 == 0) {flag = 0;break;}
                            int t = (b[i+1])/(a[i+1]+d2);
                            if(t*(a[i+1]+d2) != b[i+1]){flag = 0;break;}
                            d1 = t;break;
                        }
                    }
                    FOR(i,0,2){
                        if(((S&T)>>i)&1) flag &= ((a[i+1]+d2)*d1==b[i+1]);
                        else if((S>>i)&1) flag &=  (a[i+1]*d1==b[i+1]);
                        else if((T>>i)&1) flag &= (a[i+1]+d2==b[i+1]);
                        else flag &= (a[i+1]==b[i+1]);
                    }
                }
                if(flag) return 2;
            }
        }
    }

    return 3;
}

signed main(){
//    freopen("test.in","r",stdin);
//    freopen("test1.out","w",stdout);
    int T;scanf("%lld",&T);
    while(T--) printf("%lld\n",Solve());
    return 0;
}


