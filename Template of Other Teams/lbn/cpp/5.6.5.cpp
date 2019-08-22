#include<bits/stdc++.h>//行列式+矩阵树定理+模非质数意义下的高斯消元
#define N 111
using namespace std;
int n,m,i,j,k,x,y;bool f;
long long a[N][N],A,B,t,ans,M=1e9;
int main(){
    scanf("%d%d%d",&n,&m,&M);//模一个非质数
    for(i=1;i<=m;i++){
        scanf("%d%d",&x,&y);//一条无向边 
        a[x][x]++;a[y][y]++;//度数矩阵+1
        a[x][y]--;a[y][x]--;//邻接矩阵-1
    }
    for(i=1;i<n;i++)for(j=1;j<n;j++)(a[i][j]+=M)%=M;//均变为非负数
    for(ans=i=1;i<n;i++){ 
        for(j=i+1;j<n;j++)
            for(A=a[i][i],B=a[j][i];B;){//使用辗转相除法
                t=A/B,A%=B,swap(A,B);//GCD
                for(k=i;k<n;k++)
(a[i][k]+=M-t*a[j][k]%M)%=M;//将第j行式子代入到第i行中 
                f^=1;//记录交换次数
                for(k=i;k<n;k++)swap(a[i][k],a[j][k]);//交换两行 
            }
        if(!a[i][i])return puts("0"),0;//无解
        (ans*=a[i][i])%=M;//将每个a(i,i)都乘到答案中 
    }
    printf("%lld",f?(M-ans)%M:ans);//交换次数的奇偶对答案有影响 
}
