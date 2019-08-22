include<bits/stdc++.h>//画圈圈
#define M 123456791
using namespace std;
char s[15];
struct Q{int x,y;}q[8888888];
int n,m,i,j,h,t,W,S,x,y,z,p,en,ans,a[15],u[15][22],f[2][4444444],v[2][4444444];
int G(int x,int q1,int q2){int k=0,i=m+1;for(;i;i--)k=k*3+(i==x?q1:(i==x+1?q2:a[i]));return k;}
void up(int x,int S,int z){
	x++;int o=x&1;
	if(v[o][S]!=x)v[o][S]=x,f[o][S]=0,q[++t]=Q{x,S};
	f[o][S]=(f[o][S]+z)%M;
}
int main(){
	for(memset(u,1,sizeof(u)),scanf("%d%d",&n,&m),i=1;i<=n;i++)
		for(scanf("%s",s+1),j=1;j<=m;j++)
			if(s[j]=='#')u[j][i]=1;else if(s[j]=='*')u[j][i]=2;else u[j][i]=0;
	for(en=n*m-1;u[en%m+1][en/m+1];en--);
	for(q[f[0][0]=v[0][0]=t=1]=Q{0,0};h<t;){
		W=q[++h].x;S=q[h].y;z=f[W&1][S];x=W%m+1;y=W/m+1;
		if(W%m==0)S*=3;for(i=1,j=S;i<=m+1;i++,j/=3)a[i]=j%3;
		if(u[x][y]){
			for(p=0,i=1;i<x;i++)if(a[i])p^=1;
			if(u[x][y]==1&&!p||u[x][y]==2&&p)up(W,G(x,0,0),z);
		}else if(a[x]==1&&a[x+1]==2&&W==en){ans=(ans+z)%M;}else//最后一个点形成回路，累加答案
		if(a[x]==1&&a[x+1]==2||a[x]==2&&a[x+1]==1)up(W,G(x,0,0),z);else//可以多个回路
		if(!a[x]&&!a[x+1]){
			if(!u[x][y+1]&&!u[x+1][y])up(W,G(x,1,2),z);
		}else if(!a[x]){ 
			if(!u[x+1][y])up(W,G(x,0,a[x+1]),z);
			if(!u[x][y+1])up(W,G(x,a[x+1],0),z);
		}else if(!a[x+1]){
			if(!u[x+1][y])up(W,G(x,0,a[x]),z);
			if(!u[x][y+1])up(W,G(x,a[x],0),z);
		}else if(a[x]==a[x+1]){
			if(a[x]==1)for(j=0,i=x+2;i<=m+1;i++){
				if(a[i]==1)j--;if(a[i]==2)j++;
				if(j>0){a[i]=1;break;}
			}else for(j=0,i=x-1;i;i--){
				if(a[i]==1)j++;if(a[i]==2)j--;
				if(j>0){a[i]=2;break;}
			}
			up(W,G(x,0,0),z);
		}
	}
	printf("%d",ans);
}
