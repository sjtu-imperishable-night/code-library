#include<bits/stdc++.h>
#define N 2222
int n,i,j;double ans,v,x,X[N],f[N][N];
int main(){
	scanf("%d",&n);
	for(i=0;i<n;i++)scanf("%lf%lf",&X[i],&f[i][0]);//f[i,0]即yi 
	for(i=1;i<n;i++)//递推n阶差商 
 		for(j=1;j<=i;j++)
			f[i][j]=(f[i][j-1]-f[i-1][j-1])/(X[i]-X[i-j]);
	scanf("%lf",&x);//求f(x) 
	ans=f[0][0];//一开始答案为f(x0) 
	v=1;//记录目前所有(x-X[i])之积为v，初值为1 
	for(i=1;i<n;i++){
		v*=(x-X[i-1]);//累乘 
		ans+=f[i][i]*v;//累计答案 
	}
	printf("%.6lf\n",ans);
}
