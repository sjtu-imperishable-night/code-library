#include<bits/stdc++.h>
#define N 1111111
#define fr(i,n) for(int i=1;i<=n;i++)
using namespace std;
int n,i,p,id,L[N],F[N],c[N][26],df[N],sk[N],f[N],_f[N],pre[N];
char s[N];
void add(int z,int n){
	for(;s[n-L[p]-1]!=s[n];p=F[p]);
	if(!c[p][z]){
		int q=++id,k=F[p];
		L[q]=L[p]+2;
		for(;s[n-L[k]-1]!=s[n];k=F[k]);
		F[q]=c[k][z];c[p][z]=q;
		df[q]=L[q]-L[F[q]];
		sk[q]=(df[q]==df[F[q]]?sk[F[q]]:F[q]);
	}
	p=c[p][z];
}
int main(){
	scanf("%s",s+1);n=strlen(s+1);
	id=F[0]=1;L[1]=-1;_f[0]=1; 
	fr(i,n)f[i]=1e9;
	fr(i,n){
		add(s[i]-'a',i);
		for(int x=p;x;x=sk[x]){
			_f[x]=i-L[sk[x]]-df[x];
			if(df[F[x]]==df[x]&&f[_f[x]]>f[_f[F[x]]])_f[x]=_f[F[x]];
			if(f[i]>f[_f[x]]+1)f[i]=f[_f[x]]+1,pre[i]=_f[x];
		}
	}
	printf("%d\n",f[n]==1e9?-1:f[n]);
}
