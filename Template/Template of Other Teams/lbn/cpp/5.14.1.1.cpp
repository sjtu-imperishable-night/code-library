#include<bits/stdc++.h>
#define N 2222
int n,i,j;double ans,v,x,X[N],Y[N];
double lagrange(int n,double x,double X[],double Y[]){//n为点数，x为要求的f(x),f(X[i])=Y[i]
	int i,j;double ans,v;
	for(i=1;i<=n;i++){
		for(v=j=1;j<=n;j++)if(i!=j)v*=(x-X[j])/(X[i]-X[j]);
		ans+=v*Y[i];
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%lf%lf",&X[i],&Y[i]);
	scanf("%lf",&x);
	printf("%.6lf",lagrange(n,x,X,Y));
}

