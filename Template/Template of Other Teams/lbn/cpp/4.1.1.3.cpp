#include<bits/stdc++.h>
#define M 111111
using namespace std;
struct Complate_Package{
	int V_sum,a[M],b[M],f[M];//V_sum为体积上限，f[i]为i体积最大价值
	void add_new(int V,int val,int cnt){//加入一件新物品
		int d,j,h,t,x,y;
		for(d=0;d<V;d++){
			h=1,t=0;
			for(j=0;j<=(V_sum-d)/V;j++){
				x=j;y=f[j*V+d]-j*val;
				for(;h<=t&&b[t]<=y;t--);
				a[++t]=x;b[t]=y;
				if(a[h]<j-cnt)h++;
				f[j*V+d]=b[h]+j*val;
			}
		}
	}
	void init(){//初始化
		memset(f,0,sizeof(f));
		scanf("%d",&V_sum);
	}
	int getmax(){//得到最大值
		int an=0,i;
		for(i=0;i<=V_sum;i++)an=max(an,f[i]);
		return an;
	}
}F;
int main(){
	int T,n,i,x,y,z;
	scanf("%d",&T);
	for(;T--;){
		F.init();
		scanf("%d",&n);
		for(i=1;i<=n;i++){
			scanf("%d%d%d",&x,&y,&z);
			F.add_new(x,y,z);
		}
		printf("%d\n",F.getmax());
	}
}
