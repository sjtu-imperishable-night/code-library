#include<cstdio>

using namespace std;

int a[10][10];
int main(){
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			scanf("%d",&a[i][j]);
	int ans=0;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			for(int k=0;k<10;k++)
				for(int l=0;l<10;l++){
					int m=a[a[a[a[0][i]][j]][k]][l];
					for(int o=0;o<10;o++)
						if(o!=i&&a[a[a[a[a[0][o]][j]][k]][l]][m]==0)
							goto ed;
					for(int o=0;o<10;o++)
						if(o!=j&&a[a[a[a[a[0][i]][o]][k]][l]][m]==0)
							goto ed;
					for(int o=0;o<10;o++)
						if(o!=k&&a[a[a[a[a[0][i]][j]][o]][l]][m]==0)
							goto ed;
					for(int o=0;o<10;o++)
						if(o!=l&&a[a[a[a[a[0][i]][j]][k]][o]][m]==0)
							goto ed;
					for(int o=0;o<10;o++)
						if(o!=m&&a[a[a[a[a[0][i]][j]][k]][l]][o]==0)
							goto ed;
					if(i!=j&&a[a[a[a[a[0][j]][i]][k]][l]][m]==0)
						goto ed;
					if(j!=k&&a[a[a[a[a[0][i]][k]][j]][l]][m]==0)
						goto ed;
					if(k!=l&&a[a[a[a[a[0][i]][j]][l]][k]][m]==0)
						goto ed;
					if(l!=m&&a[a[a[a[a[0][i]][j]][k]][m]][l]==0)
						goto ed;
					continue;
					ed:;
					ans++;
				}
	printf("%d\n",ans);
}
