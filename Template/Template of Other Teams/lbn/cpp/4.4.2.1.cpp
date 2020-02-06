#include<bits/stdc++.h>//石子合并 
#define N 3030
int n,i,j,k,x,S[N],f[N][N],to[N][N];
int main(){
    memset(f,63,sizeof f);
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%d",&x),S[i]=S[i-1]+x;
    for(i=1;i<=n;i++)f[i][i]=0,to[i][i+1]=i;//to为最优决策 
    for(i=1;i<n;i++)f[i][i+1]=S[i+1]-S[i-1];
    for(i=n;i;i--)
        for(j=i+2;j<=n;j++){
            for(k=to[i][j-1];k<=to[i+1][j];k++)//只需在to[i][j-1]~to[i+1][j]找即可 
                if(f[i][j]>f[i][k]+f[k+1][j]+S[j]-S[i-1])
                    f[i][j]=f[i][to[i][j]=k]+f[k+1][j]+S[j]-S[i-1];
        }
    printf("%d",f[1][n]);
}
