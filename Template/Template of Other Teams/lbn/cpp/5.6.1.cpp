#define eps 1e-8
int gauss(double a[][N],bool l[],double ans[],const int&n){
	int res=0,r=0,i,j,k;
	for(i=0;i<n;i++)l[i]=0;
	for(i=0;i<n;i++){
		for(j=r;j<n;j++)if(fabs(a[j][i])>eps){
			for(k=i;k<=n;k++)swap(a[j][k],a[r][k]);
			break;
		}
		if(fabs(a[r][i])<eps){
			res++;
			continue;
		}
		for(j=0;j<n;j++)if(j!=r&&fabs(a[j][i])>eps){
			double p=a[j][i]/a[r][i];
			for(k=i;k<=n;k++)a[j][k]-=p*a[r][k];
		}
		l[i]=1;r++;
	}
	for(i=0;i<n;i++)if(l[i])for(j=0;j<n;j++)if(fabs(a[j][i])>eps)ans[i]=a[j][n]/a[j][i];
	return res;
}
