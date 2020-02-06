#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const double eps=1e-8;
const double PI=acos(-1.0);
struct Complex
{
    double real,image;
    Complex(double _real,double _image)
    {
        real=_real;
        image=_image;
    }
    Complex(){real=0;image=0;}
};
 
Complex operator + (const Complex &c1, const Complex &c2)
{
    return Complex(c1.real + c2.real, c1.image + c2.image);
}
 
Complex operator - (const Complex &c1, const Complex &c2)
{
    return Complex(c1.real - c2.real, c1.image - c2.image);
}
 
Complex operator * (const Complex &c1, const Complex &c2)
{
    return Complex(c1.real*c2.real - c1.image*c2.image, c1.real*c2.image + c1.image*c2.real);
}
 
int rev(int id,int len)
{
    int ret=0;
    for(int i=0;(1<<i)<len;i++)
    {
        ret<<=1;
        if(id&(1<<i))
			ret|=1;
    }
    return ret;
}
Complex* IterativeFFT(Complex* a,int len,int DFT)
{
    Complex* A=new Complex[len];
    for(int i=0;i<len;i++)
        A[rev(i,len)]=a[i];
    for(int s=1;(1<<s)<=len;s++)
    {
        int m=(1<<s);
        Complex wm=Complex(cos(DFT*2*PI/m),sin(DFT*2*PI/m));
        for(int k=0;k<len;k+=m)
        {
            Complex w=Complex(1,0);
            for(int j=0;j<(m>>1);j++)
            {
                Complex t=w*A[k+j+(m>>1)];
                Complex u=A[k+j];
                A[k+j]=u+t;
                A[k+j+(m>>1)]=u-t;
                w=w*wm;
            }
        }
    }
    if(DFT==-1)
	for(int i=0;i<len;i++)
	{
		A[i].real/=len;
		A[i].image/=len;
	}
    return A;
}
char s[101010],t[101010];
Complex a[202020],b[202020],c[202020];
int pr[202020];
int main()
{
	int len;
	scanf("%d",&len);
	scanf("%s",s);
	scanf("%s",t);
	for(int i=0;i<len;i++)
		a[i]=Complex(s[len-i-1]-'0',0);
	for(int i=0;i<len;i++)
		b[i]=Complex(t[len-i-1]-'0',0);
	int tmp=1;
	while(tmp<=len)
		tmp*=2;
	len=tmp*2;
	Complex* aa=IterativeFFT(a,len,1);
	Complex* bb=IterativeFFT(b,len,1);
	for(int i=0;i<len;i++)
		c[i]=aa[i]*bb[i];
	Complex* ans=IterativeFFT(c,len,-1);
	for(int i=0;i<len;i++)
		pr[i]=round(ans[i].real);
	for(int i=0;i<=len;i++)
	{
		pr[i+1]+=pr[i]/10;
		pr[i]%=10;
	}
	bool flag=0;
	for(int i=len-1;i>=0;i--)
	{
		if(pr[i]>0)
			flag=1;
		if(flag)
			printf("%d",pr[i]);
	}
	printf("\n");
    return 0;
}
