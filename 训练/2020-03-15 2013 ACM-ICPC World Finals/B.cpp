#include<bits/stdc++.h>
using namespace std;

__float128 t;
double r;

__float128 qpow(__float128 a,int k)
{
	__float128 ret=1;
	while(k)
	{
		if(k&1)
		{
			if(1e200/a<ret)
				return 1e200;
			ret*=a;
		}
		a*=a;
		k/=2;
	}
	return ret;
}

__float128 calc(int N,int M)
{
	__float128 ret=0;
	__float128 tM=qpow(t,M),tN=qpow(t,N);
	if(tM > 1e199 || tN > 1e199)
		return -1e300;
	//cout<<N<<" "<<M<<" "<<double(tM)<<" "<<double(tN)<<" "<<endl;
	ret += (tM - 1)*N;
	ret += (tN - tM)*r*M/100;
	ret /= tN - 1;
	ret -= M;
	return ret;
}

__float128 sf2(int N)
{
	int L=1,R=1000000;
	while(L<R)
	{
		int M1=L+(R-L)/3,M2=R-(R-L)/3;
		if(calc(N+M1,M1)<calc(N+M2,M2))
			L=M1+1;
		else
			R=M2-1; 
	}
	return calc(N+L,L);
}

__float128 sf1()
{
	int L=1,R=1000000;
	while(L<R)
	{
		int M1=L+(R-L)/3,M2=R-(R-L)/3;
		if(sf2(M1)<sf2(M2))
			L=M1+1;
		else
			R=M2-1; 
	}
	return sf2(L);
}

int main()
{
	double p;
	
	scanf("%lf%lf",&r,&p);
	t=100-p;
	t/=p;
	printf("%.10f\n",max(0.0,double(sf1())));
	return 0;
}
