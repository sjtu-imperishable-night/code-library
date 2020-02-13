#include<cstdio>
#include<algorithm>
using namespace std;

int l[200001],r[200001];
struct dn{int x,y;}a[100001];
bool operator<(dn u,dn v){
	return u.x<v.x;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		l[i]=r[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+m+1);
	for(int i=1;i<=m;i++){
		l[a[i].y+1]=l[a[i].y];
		r[a[i].y]=r[a[i].y+1];
	}
	for(int i=1;i<=n;i++)
		printf("%d%c",r[i]-l[i]+1,i==n?'\n':' ');
}
