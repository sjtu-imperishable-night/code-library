#include<cstdio>
#include<algorithm>
using namespace std;

void gcd(int a,int b,int&d,int&x,int&y){
	if(!b)d=a,x=1,y=0;
	else gcd(b,a%b,d,y,x),y-=a/b*x;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		int d,x,y;
		gcd(a,b,d,x,y);
		if(d<=50000)
			printf("3\n0 0\n%d %d\n%d %d\n",a,b,abs(y),abs(x));
		else
			printf("4\n0 0\n%d %d\n%d %d\n%d %d\n",a-1,b,a/d,b/d,a,b-1);
	}
}

