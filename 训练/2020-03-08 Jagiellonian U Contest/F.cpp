#include<bits/stdc++.h>
using namespace std;

struct Point{
	int x,y;
}p[101010];

const int times=80;
double ansx=0,ansy=0;

int n;

double calc(double x,double y)
{
	double ret=0;
	for(int i=1;i<=n;i++)
		ret+=sqrt((x-p[i].x)*(x-p[i].x)+(y-p[i].y)*(y-p[i].y));
	return ret;
}

double ef2(double x)
{
	int _times=times;
	double l=-1000000,r=1000000;
	while(_times--)
	{
		double mid1=(l+l+r)/3,mid2=(l+r+r)/3;
		if(calc(x,mid1)<calc(x,mid2))
			r=mid2;
		else
			l=mid1;
	}
	ansy=l;
	return calc(x,l);
}

void ef1()
{
	int _times=times;
	double l=-1000000,r=1000000;
	while(_times--)
	{
		double mid1=(l+l+r)/3,mid2=(l+r+r)/3;
		if(ef2(mid1)<ef2(mid2))
			r=mid2;
		else
			l=mid1;
	}
	ansx=l;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&p[i].x,&p[i].y);
		
		ef1();
		printf("%.10f %.10f\n",ansx,ansy);
		
		
	}
	return 0;
}
