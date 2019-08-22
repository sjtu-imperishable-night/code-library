#include<bits/stdc++.h>//BZOJ3744，在线逆序对
using namespace std;
const int N=50005,BS=200,BN=250;
int n,m,i,j,sum,now,ans,x,y,l,r,bx,by,b[N],c[N],a[N],v[N],d[253][253],f[253][N],g[253][N];
void add(int x){for(;x<=n;x+=x&-x)c[x]++;}
int query(int x){for(sum=0;x;x-=x&-x)sum+=c[x];return sum;}
int main(){
	for(scanf("%d",&n),i=1;i<=n;i++)scanf("%d",&a[i]),v[i]=a[i];
	sort(v+1,v+n+1);for(i=1;i<=n;i++)a[i]=lower_bound(v+1,v+n+1,a[i])-v;
	for(j=1;j<=BN;j++)
		for(memset(c,0,sizeof(c)),now=0,i=(j-1)*BS+1;i<=n;i++)
			now+=query(n)-query(a[i]),add(a[i]),
			d[j][(i-1)/BS+1]=now;
	for(memcpy(b,a,sizeof(b)),j=1;j<=BN;j++){
		l=(j-1)*BS+1;r=j*BS+1;sort(b+l,b+r);
		memcpy(f[j],f[j-1],sizeof(f[j]));memcpy(g[j],g[j-1],sizeof(g[j]));
	for(i=1;i<=n;i++)f[j][i]+=(b+r-upper_bound(b+l,b+r,i)),g[j][i]+=(lower_bound(b+l,b+r,i)-b-l);
	for(scanf("%d",&m);m--;){
		memset(c,0,sizeof(c));
		scanf("%d%d",&x,&y);x^=ans;y^=ans;ans=0;
		bx=(x-1)/BS+1;by=(y-1)/BS+1;
		if(bx+2<=by){
			ans=d[bx+1][by-1];
			for(i=y;i>(by-1)*BS;i--)ans+=query(a[i]-1)+f[by-1][a[i]]-f[bx][a[i]],add(a[i]);
			for(i=bx*BS;i>=x;i--)ans+=query(a[i]-1)+g[by-1][a[i]]-g[bx][a[i]],add(a[i]);
		}else for(i=y;i>=x;i--)ans+=query(a[i]-1),add(a[i]);
		printf("%d\n",ans);
	}
}
