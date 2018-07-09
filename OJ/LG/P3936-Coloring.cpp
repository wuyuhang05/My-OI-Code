#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cmath>
#include <cstdlib>
const int MAXN = 50 + 5;
const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};
const double EPS = 1e-15;
int N,M,C;
int p[MAXN];
int E[MAXN];
int A[25][25],B[25][25],sum,ans = 100000000;
int out[25][25];
int get(int x,int y){
    int ret = 0;
    for(int i = 0;i < 4;i++){
        if(A[x][y] != A[x + dx[i]][y + dy[i]])
            ret++;
    }
    return B[x][y] = ret;
}
void update(int x){
    if(ans <= x) return;
    ans = x;
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= M;j++)
            out[i][j] = A[i][j];
}
double Rand(){
    return 1.0*(rand()%100000000)/100000000;
}
void SA(double T){
    while(T > EPS){
        T *= 0.99999;
        int x1 = 1 + rand() % N,x2 = 1 + rand() % N;
        int y1 = 1 + rand() % M,y2 = 1 + rand() % M;
        std::swap(A[x1][y1],A[x2][y2]);
        int t = sum;
        t -= B[x1][y1] + B[x2][y2];
        t += get(x1,y1) + get(x2,y2);
        if(t < sum || exp((sum-t)/T) > Rand()){
            update(sum = t);
            continue;
        }
        std::swap(A[x1][y1],A[x2][y2]);
        get(x1,y1);get(x2,y2);
    }
}
int main(){
    srand(19260817);
    scanf("%d%d%d",&N,&M,&C);
    for(int i = 1;i <= C;i++)
        scanf("%d",&p[i]);
    int round = 5;
    while(round--){
        for(int i = 1;i <= C;i++) E[i] = p[i];
        for(int i = 1;i <= N;i++)
            for(int j = 1,x = 1;j <= M;j++){
                x = 1 + rand()%C;
                while(!E[x]) x = rand()%C + 1;
                A[i][j] = x;E[x]--;
            }
        sum = 0;
        for(int i = 1;i <= N;i++)
            for(int j = 1;j <= M;j++)
                sum += get(i,j);
        update(sum);
        SA(100000000);
    }
    for(int i = 1;i <= N;i++,puts(""))
        for(int j = 1;j <= M;j++)
            printf("%d ",out[i][j]);
    return 0;
}
