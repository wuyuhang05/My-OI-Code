#include <iostream>
#include <cstdio>
#include <cstring>

struct Matrix{
    typedef long long LL;
    static const int MAXN = 500 + 5;
    static const int ha = 1e9 + 7;
    LL data[MAXN][MAXN];
    int N,M;

    void clear(int n=0,int m=0){
        memset(data,0,sizeof(data));
        N = n;M = m;
    }

    void Read(int n,int m){
        for(int i = 0;i < n;i++)
            for(int j = 0;j < m;j++)
                scanf("%lld",&data[i][j]);
        N = n;M = m;
    }

    void Print(){
        for(int i = 0;i < N;i++)
            for(int j = 0;j < M;j++){
                data[i][j] = (data[i][j] + ha) % ha;
                printf("%lld%c",data[i][j],(j == M - 1) ? '\n' : ' ');
            }
    }

    Matrix operator * (const Matrix &b) const{
        Matrix ret;
        ret.clear(N,b.M);
        for(int i = 0;i < N;i++)
            for(int j = 0;j < b.M;j++)
                for(int k = 0;k < M;k++)
                    ret.data[i][j] = (ret.data[i][j] + ((data[i][k] * b.data[k][j]) % ha)) % ha;
        //ret.N = N;ret.M = b.M;
        return ret;
    }

    Matrix operator ^ (LL y) const{
        Matrix t = (*this),ans = (*this);
        for(y--;y;y >>= 1,t = t * t){
            if(y & 1) ans = ans * t;
        }
        return ans;
    }

    Matrix operator + (const Matrix &b){
        Matrix a = (*this),ret;
        ret.clear(N,M);
        for(int i = 0;i < N;i++)
            for(int j = 0;j < M;j++)
                ret.data[i][j] = ((a.data[i][j] % ha) + (b.data[i][j] % ha)) % ha;
        return ret;
    }

    Matrix operator - (const Matrix &b){
        Matrix a = (*this),ret;
        ret.clear(N,M);
        for(int i = 0;i < N;i++)
            for(int j = 0;j < M;j++)
                ret.data[i][j] = ((a.data[i][j] % ha) - (b.data[i][j] % ha)) % ha;
        return ret;
    }
};

int main(){
    Matrix a,ans;
    Matrix::LL N,K;
    scanf("%lld%lld",&N,&K);
    a.clear(N,N);ans.clear(N,N);
    a.Read(N,N);
    ans = a^K;
    ans.Print();
    //getchar();getchar();
    return 0;
}
