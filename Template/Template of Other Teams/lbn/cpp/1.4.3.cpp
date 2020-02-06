#include<bits/stdc++.h>
#define N 505
#define CL(a) memset(a,0,sizeof(a))
using namespace std;
int n,i,j,x,a[N][N],b[N][N],la[N],lb[N],V[N];
bool ff;
map<string,int>mp,pm;
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf("%d",&a[i][j]);//男生对女生喜欢程度的排名
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf("%d",&x),b[i][x]=n-j;//女生对每个男生的排名转化成喜欢程度
	for(;;){
		for(ff=0,i=1;i<=n;i++)if(!la[i]){//未匹配的男生
			x=a[i][++V[i]];ff=1;
			if(!lb[x]||b[x][lb[x]]<b[x][i])la[lb[x]]=0,lb[x]=i,la[i]=x;//对女生来说，如果更好，则替换
		}
		if(!ff)break;
	}
	for(i=1;i<=n;i++)printf("%d %d\n",i,la[i]);
}
