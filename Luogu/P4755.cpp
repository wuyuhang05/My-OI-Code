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
const int MAXM = 18;

int sm[MAXN<<5],lc[MAXN<<5],rc[MAXN<<5],tot;

inline void update(int prev,int &v,int l,int r,int p){
    sm[v = ++tot] = sm[prev]+1;lc[v] = lc[prev];rc[v] = rc[prev];
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc[prev],lc[v],l,mid,p);
    else update(rc[prev],rc[v],mid+1,r,p);
}

inline int query(int x,int y,int l,int r,int L,int R){
    if(L > R) return 0;
    if(l == L && r == R) return sm[y]-sm[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc[x],lc[y],l,mid,L,R);
    if(L > mid) return query(rc[x],rc[y],mid+1,r,L,R);
    return query(lc[x],lc[y],l,mid,L,mid)+query(rc[x],rc[y],mid+1,r,mid+1,R);
}

std::vector<int> S;
int a[MAXN],n,root[MAXN],m;
LL ans;
int mx[MAXM+1][MAXN],ps[MAXM+1][MAXN];
int pc[MAXN];

inline int calc(int l,int r){
    int c = pc[r-l+1];
    if(mx[c][l] > mx[c][r-(1<<c)+1]) return ps[c][l];
    return ps[c][r-(1<<c)+1];
}

int sm1[MAXN];

inline void work(int l,int r){
    if(l >= r) return;
    int mid = calc(l,r),val = S[a[mid]-1];
    if(mid-l < r-mid){
        FOR(i,l,mid-1){
            int t = val/S[a[i]-1];t = std::upper_bound(all(S),t)-S.begin();
            ans += query(root[mid],root[r],1,m,1,t);
        }
    }
    else{
        FOR(i,mid+1,r){
            int t = val/S[a[i]-1];t = std::upper_bound(all(S),t)-S.begin();
            ans += query(root[l-1],root[mid-1],1,m,1,t);
        }
    }
    ans += sm1[r]-sm1[l-1]-(S[a[mid]-1]==1);
    work(l,mid-1);work(mid+1,r);
}

int main(){
    pc[0] = -1;FOR(i,1,MAXN-1) pc[i] = pc[i>>1]+1;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),S.pb(a[i]),sm1[i] = sm1[i-1]+(a[i]==1);
//    DEBUG(sm1[4]);
    std::sort(all(S));S.erase(std::unique(all(S)),S.end());
    FOR(i,1,n) a[i] = std::lower_bound(all(S),a[i])-S.begin()+1;m = S.size();
    FOR(i,1,n) update(root[i-1],root[i],1,m,a[i]);
    FOR(i,1,n) mx[0][i] = a[i],ps[0][i] = i;
    FOR(i,1,MAXM){
        for(int j = 1;j+(1<<(i-1)) < MAXN;++j){
            if(mx[i-1][j] > mx[i-1][j+(1<<(i-1))]){
                mx[i][j] = mx[i-1][j];
                ps[i][j] = ps[i-1][j];
            }
            else{
                mx[i][j] = mx[i-1][j+(1<<(i-1))];
                ps[i][j] = ps[i-1][j+(1<<(i-1))];
            }
        }
    }
    work(1,n);
    printf("%lld\n",ans+sm1[n]);
    return 0;
}
