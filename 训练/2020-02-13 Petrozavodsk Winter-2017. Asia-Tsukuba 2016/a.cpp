#include<cstdio>

using namespace std;

int a[300001],b[200001];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		a[i]=n-i+1;
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i+n]);
	for(int i=n+m;i;i--)
		if(!b[a[i]]){
			printf("%d\n",a[i]);
			b[a[i]]=1;
		}
}
