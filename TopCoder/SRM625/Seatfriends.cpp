// BEGIN CUT HERE

// END CUT HERE
#include <iostream>
#include <cstring>
#include <cstdio>

#define LL long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
const int ha = 1000000007;
const int MAXN = 2000 + 7;
LL f[MAXN][MAXN];
LL yh[MAXN][MAXN];

class Seatfriends {
public:
    int N=0,K=0,G=0;

    inline void init(){
        for(int i = 0;i <= N;i++){
            yh[i][0] = 1;
            for(int j = 1;j <= i;j++)
                yh[i][j] = (yh[i-1][j] + yh[i-1][j-1]) % ha;
        }
    }

    LL dp(){
        if(N == K) --K;
        f[1][1] = 1;
        for(int i = 1;i < K;i++){
            for(int j = 1;j <= G;j++){
                if(!f[i][j]) continue;
                if(j > 1)
                    f[i+1][j-1] = (f[i+1][j-1] + f[i][j] * j) % ha;
                f[i+1][j] = (f[i+1][j] + f[i][j] * j * 2) % ha;
                if(j < G)
                    f[i+1][j+1] = (f[i+1][j+1] + f[i][j] * j) % ha;
            }
        }
        LL ans = 0;
        for(int i = 1;i <= G;i++){
            ans = (ans + f[K][i] * yh[N-K-1][i-1]) % ha;
        }
        ans = (ans * N) % ha;
        return ans;
    }


    int countseatnumb(int N,int K,int G){
        this->N = N;this->K = K;this->G = G;
        init();
        return (int)(dp()%ha);
    }
    
    // BEGIN CUT HERE
    
    
    
    // END CUT HERE
};

// BEGIN CUT HERE

// END CUT HERE
