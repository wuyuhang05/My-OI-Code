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

const int MAXN = 50000+5;
const int MAXM = 16;
const int ha = 998244353;
int n,a[MAXN],Log[MAXN];

struct DS1{
    int g[MAXM+1][MAXN];

    inline void build(){
        FOR(i,1,n) g[0][i] = a[i];
        FOR(i,1,MAXM){
            for(int j = 0;j+(1<<(i-1))<MAXN;++j){
                g[i][j] = std::__gcd(g[i-1][j],g[i-1][j+(1<<(i-1))]);
            }
        }
    }

    inline int calc(int l,int r){
        if(l > r) std::swap(l,r);
        int c = Log[r-l+1];
        return std::__gcd(g[c][l],g[c][r-(1<<c)+1]);
    }
}st;

struct DS2{
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)
    int now;
    int sm[MAXN<<2],tag[MAXN<<2],ts[MAXN<<2];

    inline void check(int x){
        if(ts[x] == now) return;
        sm[x] = tag[x] = 0;ts[x] = now;
    }

    inline void reset(){
        now++;
    }

    inline void cover(int x,int l,int r,int d){
        check(x);
        (sm[x] += 1ll*(r-l+1)*d%ha)%=ha;(tag[x] += d)%=ha;
    }

    inline void pushdown(int x,int l,int r){
        check(x);
        if(tag[x]){
            int mid = (l + r) >> 1;
            cover(lc,l,mid,tag[x]);cover(rc,mid+1,r,tag[x]);
            tag[x] = 0;
        }
    }

    inline void modify(int x,int l,int r,int L,int R,int d){
        if(L > R) return;
        check(x);
        if(l == L && r == R){cover(x,l,r,d);return;}
        int mid = (l+r)>>1;pushdown(x,l,r);
        if(R <= mid) modify(lc,l,mid,L,R,d);
        else if(L > mid) modify(rc,mid+1,r,L,R,d);
        else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
        if(l != r) check(lc),check(rc);
        sm[x] = (sm[lc]+sm[rc])%ha;
    }
    

    inline int query(int x,int l,int r,int L,int R){
        if(L > R) return 0;
        check(x);
        if(l == L && r == R) return sm[x];
        int mid = (l + r) >> 1;pushdown(x,l,r);
        if(R <= mid) return query(lc,l,mid,L,R);
        if(L > mid) return query(rc,mid+1,r,L,R);
        return (query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R))%ha;
    }
}F,G;

struct Node{
    int l1,l2,r,g;// [[l1,l2],r]
    int opt;
    Node(int l1=0,int l2=0,int r=0,int g=0,int opt=0) : l1(l1),l2(l2),r(r),g(g),opt(opt) {}
    
    bool operator < (const Node &t) const {
        return g == t.g ? r < t.r : g < t.g;
    }
}A[MAXN*233];
int N;

inline int find(int x,int s,int g){ // gcd[,x]=g
    int l = 1,r = s,ans = s;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(st.calc(mid,x) < g) l = mid+1;
        else ans = mid,r = mid-1;
    }
    return ans;
}

inline int find2(int x,int s,int g){ // gcd[x,]=g
    int l = s,r = n,ans = s;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(st.calc(x,mid) < g) r = mid-1;
        else ans = mid,l = mid+1;
    }
    return ans;
}
int cf[MAXN],tot = 0;
std::vector<int> S;
inline void work(){
    N = 0;st.build();
    FOR(i,1,n){
        int now = i;
        while(now >= 1){
            int g = 0;
            int t = find(i,now,g=st.calc(now,i));
            A[++N] = Node(t,now,i,g,1);now = t-1;
        }
        now = i;
        while(now <= n){
            int g = 0;
            int t = find2(i,now,g=st.calc(i,now));
            A[++N] = Node(now,t,i,g,-1);now = t+1;
        }
    }
    std::sort(A+1,A+N+1);
    //FOR(i,1,N) if(A[i].opt == 1) printf("%d %d %d %d\n",A[i].r,A[i].l1,A[i].l2,A[i].g);
    for(int l = 1,r = 1;r <= N;l = r+1,r = l){
        while(r <= N && A[r+1].g == A[l].g) r++;
        F.reset();G.reset();//int n = S.size();
        FOR(i,l,r){
            if(A[i].opt == -1) continue;
            int t = (F.query(1,0,n+1,A[i].l1-1,A[i].l2-1)+A[i].l2-A[i].l1+1)%ha;
            F.modify(1,0,n+1,A[i].r,n,t);
        }
        (tot += F.query(1,0,n+1,n,n)) %= ha;
        ROF(i,r,l){
            if(A[i].opt == 1) continue;
            int t = (G.query(1,0,::n+1,A[i].l1+1,A[i].l2+1)+A[i].l2-A[i].l1+1)%ha;
            G.modify(1,0,n+1,1,A[i].r,t);
        }
        std::vector<int> S;
        FOR(i,l,r) S.pb(A[i].r);S.erase(std::unique(all(S)),S.end());
        int pre = 0;
        for(auto x:S){
            //[pre+1,x-1]
            int t = 1ll*(F.query(1,0,n+1,pre,pre)+1)*(G.query(1,0,n+1,x,x)+1)%ha;
            (t += ha-1) %= ha;
            (cf[pre+1] += t)%=ha;(cf[x] += ha-t)%=ha;
            pre = x;
        }
        if(pre != n){
            int t = 1ll*(F.query(1,0,n+1,pre,pre)+1)*(G.query(1,0,n+1,n,n)+1)%ha;
            (t += ha-1) %= ha;
            (cf[pre+1] += t)%=ha;
        }
        FOR(i,0,(int)S.size()-1){
            auto x = S[i];
            int l = i==0?0:S[i-1],r = i+1==(int)S.size()?n+1:S[i+1];
            int t = 1ll*(F.query(1,0,n+1,l,l)+1)*(G.query(1,0,n+1,r,r)+1)%ha;
            (t += ha-1) %= ha;
            (cf[x] += t)%=ha;(cf[x+1] += ha-t)%=ha;
        }
    }
}

int pre[MAXN],suf[MAXN];

int main(){
    Log[0] = -1;FOR(i,1,MAXN-1) Log[i] = Log[i>>1]+1;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    work();
    FOR(i,1,n) (cf[i] += cf[i-1]) %= ha;
    FOR(i,1,n) printf("%d%c",(tot+ha-cf[i])%ha," \n"[i==n]);
    return 0;
}
