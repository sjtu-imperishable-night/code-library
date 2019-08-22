#include<bits/stdc++.h>
#define N 111111
using namespace std;
int n,i;
double sqr(double x){return x*x;}
struct P{
	double x,y;
	void in(){scanf("%lf%lf",&x,&y);}
}p[N],q[N];
double dis(P a,P b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}
bool cmp(P a,P b){return a.x<b.x;}
bool cmp2(P a,P b){return a.y<b.y;}
double get(int l,int r){
	if(l>=r)return 1e20;
	if(l+1==r)return dis(p[l],p[r]);
	int i,j,t=0,md=l+r>>1;
	double ans=min(get(l,md),get(md+1,r));
	for(i=l;i<=r;i++)if(fabs(p[i].x-p[md].x)<=ans)q[++t]=p[i];
	for(sort(q+1,q+t+1,cmp2),i=1;i<t;i++)
		for(j=i+1;j<=t;j++){
			if((q[j].y-q[i].y)>ans)break;
			ans=min(ans,dis(q[i],q[j]));
		}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)p[i].in();
	sort(p+1,p+n+1,cmp);
	printf("%.7f\n",get(1,n));
}
