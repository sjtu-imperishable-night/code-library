#include<bits/stdc++.h>
#define N 100100
#define M 250200
using namespace std;
int n,m,i,j,x,y,tot,ans,v[N],X[M],Y[M],du[N],fir[N],la[M],ne[M];
void ins(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}
int main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++)scanf("%d%d",&X[i],&Y[i]),du[X[i]]++,du[Y[i]]++;
    for(i=1;i<=m;i++)//按度数大小将无向边变为有向边
	if(du[X[i]]<du[Y[i]]||du[X[i]]==du[Y[i]]&&X[i]<Y[i])
		ins(X[i],Y[i]);else ins(Y[i],X[i]);
    for(x=1;x<=n;x++){//枚举每个点当度数最小的点
        for(i=fir[x];i;i=ne[i])v[la[i]]=x;//找一步能到的点
        for(i=fir[x];i;i=ne[i])//找第一个点
		for(j=fir[y=la[i]];j;j=ne[j])//找第二个点
			if(v[la[j]]==x)ans++;//找到了三元环
    }
    printf("%d",ans);
}
