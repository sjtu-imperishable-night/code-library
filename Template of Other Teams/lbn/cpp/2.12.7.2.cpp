#include<cstdio>
#include<ext/rope>
using namespace __gnu_cxx;
rope<int> *fa[200002];
int n,m,i,x,y,p,ans,a[200002];
int find(int x){
	if(fa[i]->at(x)!=x){
		int f=find(fa[i]->at(x));
		if(f==fa[i]->at(x))return f;
		fa[i]->replace(x,f);return fa[i]->at(x);
	}
	return x;
}
void uni(int x,int y){int p=find(x),q=find(y);fa[i]->replace(q,p);}
int main(){
	scanf("%d%d",&n,&m);for(i=0;i<=n;i++)a[i]=i;
	fa[0]=new rope<int>(a,a+n+1);
	for(i=1;i<=m;i++){
		fa[i]=new rope<int>(*fa[i-1]);scanf("%d",&p);
		if(p==1)scanf("%d%d",&x,&y),uni(x^ans,y^ans);
		else if(p==2)scanf("%d",&x),fa[i]=fa[x^ans];
		else if(p==3)scanf("%d%d",&x,&y),printf("%d\n",(ans=find(x^ans)==find(y^ans)));
	}
}
