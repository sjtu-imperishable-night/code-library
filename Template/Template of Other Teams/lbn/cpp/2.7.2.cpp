#include<cstdio>//BZOJ3261
#define N 12222222
int x,i,n,m,l,r,tot,rt[N],b[N],c[N][2],s[N];char ch[9];
void ins(int x,int &y,int z,int d){
	int p=(z>>d)&1;s[y=++tot]=s[x]+1;if(d<0)return;
	c[y][p^1]=c[x][p^1];ins(c[x][p],c[y][p],z,d-1);
}
int qu(int x,int y,int z,int d){
	if(d<0)return 0;int p=(z>>d)&1;
	if(s[c[y][p^1]]-s[c[x][p^1]])return (1<<d)+qu(c[x][p^1],c[y][p^1],z,d-1);
	else return qu(c[x][p],c[y][p],z,d-1);
}
int main(){
	for(ins(0,rt[1],0,24),scanf("%d%d",&n,&m),n++,i=2;i<=n;i++)scanf("%d",&x),ins(rt[i-1],rt[i],b[i]=b[i-1]^x,24);
	for(;m--;){
		scanf("%s",ch);
		if(ch[0]=='A')scanf("%d",&x),n++,ins(rt[n-1],rt[n],b[n]=b[n-1]^x,24);
		else scanf("%d%d%d",&l,&r,&x),printf("%d\n",qu(rt[l-1],rt[r],b[n]^x,24));
	}
}