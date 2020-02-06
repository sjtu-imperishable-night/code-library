#include<bits/stdc++.h>//环套树求直径，Island
#define N 1001000
#define inf 1e15
#define LL long long
using namespace std;
int n,i,j,x,u,id,num,tot,to[N],cir[N],F[N],v[N],fir[N],ne[N*2],la[N*2];
LL z,now,ans,mv,mv2,zs,n1,n2,va[N*2],sum[N],d[N],L[N];bool c[N],vs[N],vs2[N];
void ins(int x,int y,LL z){la[++tot]=y;va[tot]=z;ne[tot]=fir[x];fir[x]=tot;}
void fcur(int x){//找环 
	v[x]=++id;
	for(int i=fir[x],y;i;i=ne[i]){
    	y=la[i];if(y==F[x])continue;
    	if(!v[y])F[y]=x,L[y]=va[i],fcur(y);
		else if(v[y]>=v[x]){
    		for(c[x]=1;x!=y;y=F[y])cir[++num]=y,zs+=L[y],sum[num+1]=sum[num]+L[y],c[y]=1;
    		cir[++num]=x;zs+=va[i];//cir[i]记录环上第i个点，c[x]记录x是否在环上 
		}
	}
} 
void gz(int x,LL z){//第一遍DFS 
	vs[x]=1;if(z>mv)mv=z,u=x;
	for(int i=fir[x];i;i=ne[i])if(!vs[la[i]]&&!c[la[i]])gz(la[i],z+va[i]);
}
void gz2(int x,LL z){//第二遍DFS 
	vs2[x]=1;if(z>mv2)mv2=z;
	for(int i=fir[x];i;i=ne[i])if(!vs2[la[i]]&&!c[la[i]])gz2(la[i],z+va[i]);
}
int main(){
	for(scanf("%d",&n),i=1;i<=n;i++)scanf("%d%lld",&x,&z),ins(i,x,z),ins(x,i,z);
	for(i=1;i<=n;i++)if(!v[i]&&!vs2[i]&&!vs[i]){
		num=0;now=-inf;zs=0;fcur(i);
		for(j=1;j<=num;j++){//对环上每个节点为根做DFS得到d[j]和该树直径更新答案 
			mv=-inf;mv2=-inf;gz(cir[j],0);
			c[cir[j]]=0;gz2(u,0);c[cir[j]]=1;
			d[j]=mv;now=max(now,mv2);
		}
		for(j=1;j<=num;j++)printf("%d %d\n",cir[j],sum[j]);
		n1=inf;n2=-inf;//n1为min(sum[j]-d[j])n2为max(sum[j]+d[j])用这两个值更新答案 
		for(j=1;j<=num;j++){//更新答案 
			now=max(now,max(sum[j]+d[j]-n1,zs-(sum[j]-d[j])+n2));
			n1=min(n1,sum[j]-d[j]);n2=max(n2,sum[j]+d[j]);
		}
		ans+=now;
	}
	printf("%lld",ans);
}
