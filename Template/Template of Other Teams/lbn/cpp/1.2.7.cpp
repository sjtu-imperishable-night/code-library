#include<bits/stdc++.h>
#define N 1111
#define M 111111
using namespace std;
int n,m,x,y,i,rt,cnt,ans,a[N],id[N],X[M],Y[M],v[N],pre[N],Z[M],low[N];
int main(){
	scanf("%d%d%d",&n,&m,&rt);//点数、边数和根
	for(i=1;i<=m;i++)scanf("%d%d%d",&X[i],&Y[i],&Z[i]);//每条边
    for(;;rt=id[rt],n=cnt){
        for(i=1;i<=n;i++)low[i]=1e9;
        for(i=1;i<=m;i++)if(X[i]!=Y[i]&&Z[i]<low[Y[i]])
			low[Y[i]]=Z[i],pre[Y[i]]=X[i];//为除根以外每个点选一条最小入边
        for(low[rt]=0,cnt=0,i=1;i<=n;i++)id[i]=v[i]=0;
        for(i=1;i<=n;i++){//找出环
            for(ans+=low[x=i];v[x]!=i&&!id[x]&&x!=rt;x=pre[x])v[x]=i;
            if(x!=rt&&!id[x])for(id[x]=++cnt,y=pre[x];x!=y;y=pre[y])id[y]=cnt;
        }
        if(!cnt)break;
        for(i=1;i<=n;i++)if(!id[i])id[i]=++cnt;
        for(i=1;i<=m;i++){//缩点
            y=Y[i];X[i]=id[X[i]];Y[i]=id[Y[i]];
            if(X[i]!=Y[i])Z[i]-=low[y];
        }
    }
    printf("%d",ans);
}
