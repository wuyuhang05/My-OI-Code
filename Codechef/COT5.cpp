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

const int MAXN = 2e5 + 5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)

struct DS{// 只处理 往右最大
    P mx[MAXN<<2];
    int sm[MAXN<<2],a[MAXN];

    inline int pushup(int x,int l,int r,int d){
        if(mx[x].fi <= d) return 0;
        if(a[l] > d) return sm[x];
        int mid = (l + r) >> 1;
        if(mx[lc].fi <= d) return pushup(rc,mid+1,r,d);
        return pushup(lc,l,mid,d)+sm[x]-sm[lc];
    }

    inline void update(int x,int l,int r,int p,int d){
        if(l == r){
            sm[x] = 1;a[l] = d;
            mx[x] = MP(d,l);
            return;
        }
        int mid = (l + r) >> 1;
        if(p <= mid) update(lc,l,mid,p,d);
        else update(rc,mid+1,r,p,d);
        mx[x] = std::max(mx[lc],mx[rc]);
        sm[x] = sm[lc]+pushup(rc,mid+1,r,mx[lc].fi);
    }

    inline void build(int x,int l,int r){
        mx[x] = MP(0,l);sm[x] = 0;
        if(l == r) {a[l] = 0;return;}
        int mid = (l + r) >> 1;
        build(lc,l,mid);build(rc,mid+1,r);
    }

    inline P qmax(int x,int l,int r,int L,int R){
        if(l == L && r == R) return mx[x];
        int mid = (l + r) >> 1;
        if(R <= mid) return qmax(lc,l,mid,L,R);
        if(L > mid) return qmax(rc,mid+1,r,L,R);
        return std::max(qmax(lc,l,mid,L,mid),qmax(rc,mid+1,r,mid+1,R));
    }

    inline int query(int x,int l,int r,int L,int R){
        if(l == L && r == R) return sm[x];
        int mid = (l + r) >> 1;
        if(R <= mid) return query(lc,l,mid,L,R);
        if(L > mid) return query(rc,mid+1,r,L,R);
        int t = qmax(lc,l,mid,L,mid).fi;
        return query(lc,l,mid,L,mid)+pushup(rc,mid+1,r,t);
    }
}T,Tr;

int n;
int k[MAXN],w[MAXN];

struct Node{
    int opt,x,y;
    Node(int opt=0,int x=0,int y=0) : opt(opt),x(x),y(y) {}
}q[MAXN];

std::vector<P> S;
std::map<int,int> now;
int N;

inline int calc(int p){
    int t1 = T.query(1,1,N,p,N);
    int t2 = Tr.query(1,1,N,N-p+1,N);
    return t1+t2;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        int opt;scanf("%d",&opt);
        if(opt == 0){
            int k,w;scanf("%d%d",&k,&w);
            q[i] = Node(opt,k,w);
            S.pb(MP(k,w));
        }
        if(opt == 1){
            int k;scanf("%d",&k);
            q[i] = Node(opt,k);
        }
        if(opt == 2){
            int u,v;scanf("%d%d",&u,&v);
            q[i] = Node(opt,u,v);
        }
    }
    std::sort(all(S));
    N = S.size();
    FOR(i,1,n){
        if(q[i].opt == 0){
            q[i].x = std::lower_bound(all(S),MP(q[i].x,q[i].y))-S.begin()+1;
        }
    }
    FOR(i,1,n){
        if(q[i].opt == 0){
            T.update(1,1,N,q[i].x,q[i].y);
            Tr.update(1,1,N,N-q[i].x+1,q[i].y);
            now[S[q[i].x-1].fi] = q[i].x;
        }
        if(q[i].opt == 1){
            T.update(1,1,N,now[q[i].x],0);
            Tr.update(1,1,N,N-now[q[i].x]+1,0);
            now[q[i].x] = 0;
        }
        if(q[i].opt == 2){
            int u = q[i].x,v = q[i].y;
            u = now[u];v = now[v];
            if(u > v) std::swap(u,v);
            int t = T.qmax(1,1,N,u,v).se;
            printf("%d\n",calc(u)+calc(v)-2*calc(t));
        }
    }
    return 0;
}
