#include<bits/stdc++.h>
using namespace std;int n,m,i,X,Y,F[100100];
struct P{int x,y,z,a,b;}an,a,b,V,p[100100];
bool cmp(P a,P b){return a.z<b.z;}
bool operator<(P a,P b){return 1ll*a.x*a.y<1ll*b.x*b.y||1ll*a.x*a.y==1ll*b.x*b.y&&a.x<b.x;}
int gf(int x){return F[x]==x?x:F[x]=gf(F[x]);}
P G(int A,int B){//将边权变为A*X[i]+B*Y[i]做最小生成树
	for(V.x=V.y=0,i=1;i<=m;i++)p[i].z=p[i].a*A+p[i].b*B;
	for(sort(p+1,p+m+1,cmp),i=1;i<=n;i++)F[i]=i;
	for(i=1;i<=m;i++)if(X=gf(p[i].x),Y=gf(Y=p[i].y),X!=Y)F[X]=Y,V.x+=p[i].a,V.y+=p[i].b;
	return V;
}
void sol(P a,P b){
	P c=G(a.y-b.y,b.x-a.x);an=min(an,c);//更新答案
	if(1ll*c.x*(a.y-b.y)+1ll*c.y*(b.x-a.x)>=-(1ll*a.x*b.y-1ll*a.y*b.x))return;//叉积大于0,无点
	sol(a,c);sol(c,b);//递归解决
}
int main(){
	an.x=an.y=1e9;
	for(scanf("%d%d",&n,&m),i=1;i<=m;i++)//读入每条边(x,y)权值为(a,b)
		scanf("%d%d%d%d",&p[i].x,&p[i].y,&p[i].a,&p[i].b);
	a=G(1,0);b=G(0,1);//先求出离x轴和y轴最近的最小生成树A和B
	an=min(a,b);sol(a,b);
	printf("%d %d\n",an.x,an.y);
}
