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
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

const int MAXN = 2e5 + 5;

int a[MAXN],b[MAXN],n,K,L;

struct A{
    int id;
    A(int id=0) : id(id) {}
    bool operator < (const A &t) const {
        return a[id] < a[t.id];
    }
};

struct B{
    int id;
    B(int id=0) : id(id) {}
    bool operator < (const B &t) const {
        return b[id] < b[t.id];
    }
};

struct AB{
    int id;
    AB(int id=0) : id(id) {}
    bool operator < (const AB &t) const {
        return a[id]+b[id] < a[t.id]+b[t.id];
    }
};

std::priority_queue<A> q1,p1;//单纯 A | B 被占
std::priority_queue<B> q2,p2;// 单纯 B | A 被占
std::priority_queue<AB> q;//一群
int flow,st[MAXN],id[MAXN];LL ans;

inline void clear(){
    while(!q1.empty()) q1.pop();while(!p1.empty()) p1.pop();
    while(!q2.empty()) q2.pop();while(!p2.empty()) p2.pop();
    while(!q.empty()) q.pop();flow = 0;
    FOR(i,1,n) st[i] = 0,id[i] = i;ans = 0;
}

inline void pop(){
    while(!q1.empty() && (st[q1.top().id]&1)) q1.pop();
    while(!q2.empty() && (st[q2.top().id]&2)) q2.pop();
    while(!q.empty() && st[q.top().id]) q.pop();
    while(!p1.empty() && st[p1.top().id] != 2) p1.pop();
    while(!p2.empty() && st[p2.top().id] != 1) p2.pop();
}

inline void gao1(){
    flow--;
    int x = q1.top().id,y = q2.top().id;
    ans += a[x]+b[y];
    st[x] |= 1;st[y] |= 2;
    if(st[x] == 1) p2.push(B(x));
    if(st[y] == 2) p1.push(A(y));
    if(x == y) flow++;
    else flow += (st[x]==3)+(st[y]==3);
}

inline void gao2(){
    int t1=-2e9,t2=-2e9,t3=-2e9;
    if(!p1.empty() && !q2.empty()) t1 = a[p1.top().id]+b[q2.top().id];
    if(!p2.empty() && !q1.empty()) t2 = b[p2.top().id]+a[q1.top().id];
    if(!q.empty()) t3 = a[q.top().id]+b[q.top().id];
    int mx = std::max(std::max(t1,t2),t3);
    if(mx == -2e9) return;
    ans += mx;
    if(mx == t1){
        int x = p1.top().id,y = q2.top().id;
        st[x] |= 1;st[y] |= 2;
        if(st[y] == 3) flow++;
        else p1.push(A(y));
        return;
    }
    if(mx == t2){
        int x = q1.top().id,y = p2.top().id;
        st[x] |= 1;st[y] |= 2;
        if(st[x] == 3) flow++;
        else p2.push(B(x));
        return;
    }
    if(mx == t3){
        int x = q.top().id;
        st[x] |= 3;return;
    }
}

inline void Solve(){
    read(n);read(K);read(L);
    FOR(i,1,n) read(a[i]);FOR(i,1,n) read(b[i]);
    clear();
    std::sort(id+1,id+n+1,[](int x,int y){return a[x] > a[y];});
    FOR(i,1,K-L) ans += a[id[i]],st[id[i]] |= 1;
    std::sort(id+1,id+n+1,[](int x,int y){return b[x] > b[y];});
    FOR(i,1,K-L) ans += b[id[i]],st[id[i]] |= 2;
    FOR(i,1,n){
        if(st[i] == 0) q1.push(A(i)),q2.push(B(i)),q.push(AB(i));
        if(st[i] == 1) q2.push(B(i)),p2.push(B(i));
        if(st[i] == 2) q1.push(A(i)),p1.push(A(i));
        if(st[i] == 3) flow++;
    }
    while(L--){
        pop();
        if(flow) gao1();
        else gao2();
    }
    printf("%lld\n",ans);
}

int main(){
    int T;read(T);
    while(T--) Solve();
    return 0;
}
