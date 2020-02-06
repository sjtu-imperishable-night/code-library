#include<bits/stdc++.h>//求sqrt(a)
#define eps 1e-8
double x,x0,a;
double F(double x){//构造F(x)=x^2-a,F(x)的解即为所求
	return x*x-a;
}
double gf(double x){//F'(x)=2x
	return x*2;
}
int main(){
	scanf("%lf",&a);
	x=1.0;//给x定一个初值
	for(;fabs(F(x))>eps;){//不断迭代直到达到精度要求
		x0=x;
		x=x-F(x)/gf(x);
	}
	printf("%.7lf\n",x);
}
