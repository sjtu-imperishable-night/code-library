#include<bits/stdc++.h>
#define N 200200
using namespace std;bool rv[N];long long B[N],S[N],mv[N],V[N],SM[N],lz[N],ST[N];int n,m,i,x,y,z,o,sz[N],sm[N],c[N][2],F[N];
bool ir(int x){return c[F[x]][0]!=x&&c[F[x]][1]!=x;}
void rev(int x){swap(c[x][0],c[x][1]);rv[x]^=1;}
void AD(int x,int z){//x子树加z 
	if(!x)return;
	mv[x]+=z;V[x]+=z;S[x]+=1ll*sz[x]*z;SM[x]=S[x]+ST[x];
	if(sm[x])sm[x]+=z;else lz[x]+=z;
}
void CG(int x,int z){//x子树变为z 
	if(!x)return;
	mv[x]=V[x]=z;S[x]=1ll*sz[x]*z;
	SM[x]=S[x]+ST[x];sm[x]=z;lz[x]=0;
}
void pd(int x){
	if(rv[x])rev(c[x][0]),rev(c[x][1]),rv[x]=0;
	if(sm[x])CG(c[x][0],sm[x]),CG(c[x][1],sm[x]),sm[x]=0;
	if(lz[x])AD(c[x][0],lz[x]),AD(c[x][1],lz[x]),lz[x]=0;
}
void ps(int x){
	S[x]=S[c[x][0]]+S[c[x][1]]+V[x];ST[x]=B[x]+ST[c[x][0]]+ST[c[x][1]];SM[x]=S[x]+ST[x];
	mv[x]=max(V[x],max(mv[c[x][0]],mv[c[x][1]]));sz[x]=sz[c[x][0]]+sz[c[x][1]]+1;
}
void R(int x){
    int y=F[x],k=c[y][0]==x;
    F[c[y][!k]=c[x][k]]=y;
    F[x]=F[y];if(!ir(y))c[F[y]][c[F[y]][1]==y]=x;
    F[c[x][k]=y]=x;ps(y);
}
void dw(int x){if(!ir(x))dw(F[x]);pd(x);}
void sy(int x){
	for(dw(x);!ir(x);R(x))if(!ir(F[x]))
		R(c[F[x]][0]==x^c[F[F[x]]][0]==F[x]?x:F[x]);
	ps(x);
}
void acs(int x){
	for(int y=0;x;c[x][1]=y,ps(x),y=x,x=F[x])
		sy(x),B[x]+=SM[c[x][1]]-SM[y];//更改虚边和 
}
void mrt(int x){acs(x);sy(x);rev(x);}
void lk(int x,int y){mrt(x);mrt(y);F[x]=y;B[y]+=SM[x];}
int main(){
	for(scanf("%d",&n),i=1;i<=n;i++)scanf("%d",&x),V[i]=mv[i]=S[i]=SM[i]=x,sz[i]=1;
	for(i=2;i<=n;i++)scanf("%d",&x),lk(x,i);
	for(scanf("%d",&m);m--;){
		scanf("%d%d%d",&o,&x,&y);if(o<=2)scanf("%d",&z);if(o!=6)mrt(x),acs(y),sy(y);
		if(o==1)AD(y,z);if(o==2)CG(y,z);
		if(o==3)printf("%lld\n",B[y]+V[y]);
		if(o==4)printf("%lld\n",mv[y]);
		if(o==5)printf("%lld\n",S[y]);
		if(o==6)lk(x,y);if(o==7)F[x]=c[y][0]=0;
	}
}
