#include<bits/stdc++.h>//BZOJ3720
#define N 60010
using namespace std;
int n,i,top,T,p,x,y,BS,ans,a[N],own[N],fa[N];
struct BL{//块的信息 
	int num[700],size;
	int ask(int k){return size-(upper_bound(num+1,num+size+1,k)-num-1);}
}blk[6000];
struct BG{//存图 
	int fir[N],tot,la[N<<1],ne[N<<1];
	void add(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}
}g1,g3;
void build(int x){//建立块状树 
	int t=own[x];blk[t].num[++blk[t].size]=a[x];
	for(int i=g1.fir[x];i;i=g1.ne[i]){
		int y=g1.la[i];
		if(fa[x]!=y){//如果没有到BS就把子节点加入  
			if(blk[t].size<BS)own[y]=t;else own[y]=++top;
			fa[y]=x;
			if(t!=own[y])g3.add(t,own[y]);
			build(y);
		}
	}
}
int QB(int x,int k){//处理整块 
	int ans=blk[x].ask(k);
	for(int i=g3.fir[x];i;i=g3.ne[i])ans+=QB(g3.la[i],k);
	return ans;
}
int Q(int x,int k){//处理散点 
	int ans=a[x]>k;
	for(int i=g1.fir[x];i;i=g1.ne[i]){
		int y=g1.la[i];
		if(fa[x]!=y)if(own[x]==own[y])ans+=Q(y,k);else ans+=QB(own[y],k);
	}
	return ans;
}
int main(){
	scanf("%d",&n);BS=sqrt(n*log(n)/log(2));
	for(i=1;i<n;i++)scanf("%d%d",&x,&y),g1.add(x,y),g1.add(y,x);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	own[1]=++top;build(1);scanf("%d",&T);
	for(i=1;i<=top;i++)sort(blk[i].num+1,blk[i].num+blk[i].size+1);
	while(T--){
		scanf("%d%d%d",&p,&x,&y);x^=ans;y^=ans;
		if(p==0)printf("%d\n",ans=Q(x,y));//询问x的子数中比y大的个数 
		else if(p==1){//修改单点权值 
			int t=own[x];
			for(int i=1;i<=blk[t].size;i++)
				if(blk[t].num[i]==a[x]){blk[t].num[i]=a[x]=y;break;}
			sort(blk[t].num+1,blk[t].num+blk[t].size+1);
		}else{//加点 
			int t=own[x];
			g1.add(x,++n);a[n]=y;fa[n]=x;
			if(blk[t].size<BS){//加到块中 
				blk[t].num[++blk[t].size]=y;
				sort(blk[t].num+1,blk[t].num+blk[t].size+1);
				own[n]=t;
			}else{//新建一个块 
				g3.add(t,++top);
				blk[top].num[++blk[top].size]=y;
				own[n]=top;
			}
		}
	}
}
