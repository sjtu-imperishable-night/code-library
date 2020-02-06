#include<bits/stdc++.h>
#define LL long long
#define N 1010
#define CL(a) memset(a,0,sizeof a)
using namespace std;
struct BN{int v[N],l;}A,B;
LL mul(LL a,LL b,LL P){//LL*LL%LL
	LL t=(a*b-LL((long double)a/P*b+1e-3)*P)%P;
	return t<0:t+P:t;
}
int cmp(BN a,BN b){//a>b->1  a=b->0   a<b->-1
	if(a.l<b.l)return -1;
	if(a.l>b.l)return 1;
	for(int i=a.l;i;i--)if(a.v[i]!=b.v[i])
		if(a.v[i]>b.v[i])return 1;else return -1;
	return 0;
}
BN num(int x){
	BN a;int q[15],i,t=0;CL(a.v);
	for(;x;x/=10)q[++t]=x%10;
	a.l=t?t:1;
	for(i=1;i<=t;i++)a.v[i]=q[t-i+1];
	return a;
}
BN getnum(){
	char s[N];BN a;int i;CL(a.v);
	scanf("%s",s+1);a.l=strlen(s+1);
	for(i=1;i<=a.l;i++)a.v[i]=s[a.l-i+1]-'0';
	return a;
}
void print(BN a){
	for(int i=a.l;i;i--)putchar(a.v[i]+48);
}
BN operator+(BN a,BN b){//高精度加法 
	BN c;int i;CL(c.v);c.l=max(a.l,b.l);
	for(i=1;i<=c.l;i++)c.v[i]=a.v[i]+b.v[i]+c.v[i],c.v[i+1]=c.v[i]/10,c.v[i]%=10;
	if(c.v[c.l+1])c.l++;
	return c;
}
BN operator-(BN a,BN b){//要保证a>=b 
	BN c;int i;CL(c.v);
	for(i=1;i<=a.l;i++){
		c.v[i]+=a.v[i]-b.v[i];
		if(c.v[i]<0)c.v[i]+=10,c.v[i+1]--;
	}
	for(c.l=a.l;!c.v[c.l]&&c.l>1;c.l--);
	return c;
}
BN operator*(BN a,BN b){//高精乘高精 
	BN c;int i,j;CL(c.v);c.l=a.l+b.l-1;
	for(i=1;i<=a.l;i++)
		for(j=1;j<=b.l;j++)
			c.v[c.l-i-j+2]+=a.v[a.l-i+1]*b.v[b.l-j+1];
	for(i=1;i<=c.l;i++)c.v[i+1]+=c.v[i]/10,c.v[i]%=10;
	if(c.v[c.l+1])c.l++;
	return c;
}
BN operator*(BN a,int b){//高精乘单精 
	BN c;int i;CL(c.v);c.l=a.l;
	for(i=1;i<=a.l;i++)c.v[i]+=a.v[i]*b,c.v[i+1]+=c.v[i]/10,c.v[i]%=10;
	for(;c.v[c.l+1];)c.l++,c.v[c.l+1]+=c.v[c.l]/10,c.v[c.l]%=10;
	return c;
}
BN operator/(BN a,BN b){//高精除高精，返回商，O(n^2) 
	if(cmp(a,b)==-1)return num(0);
	int ws=1;BN c;CL(c.v);
	for(;cmp(a,b*10)>=0;)b=b*10,ws++;
	for(c.l=ws;ws;a=a*10,ws--)
		for(;cmp(a,b)>=0;c.v[ws]++)a=a-b;
	return c;
}
BN operator/(BN a,int b){//高精除单精，O(n) 
	int i,V=0;bool f=0;BN c;CL(c.v);
	for(i=a.l;i;i--)V=V*10+a.v[i],c.v[i]=V/b,V%=b;
	for(c.l=a.l;!c.v[c.l]&&c.l>1;c.l--);
	return c;
}
BN operator%(BN a,BN b){//高精对高精取模 
	BN c=a/b;
	return a-(b*c);
}
BN operator%(BN a,int b){//高精对单精取模 
	BN c=a/b;
	return a-(c*b);
}
BN fac(int n){//阶乘 
	BN a=num(1);
	for(int i=1;i<=n;i++)a=a*i;
	return a;
}
BN operator^(BN a,int b){//高精度幂次 
	BN c=num(1);
	for(;b;b>>=1,a=a*a)if(b&1)c=c*a;
	return c;
}
BN gcd(BN a,BN b){//高精度gcd 
	if(b.l<=1&&b.v[1]==0)return a;
	return gcd(b,a%b);
}
BN sqrt(BN a){//高精度开根下取整，使用牛顿迭代法 
	BN b=num(1),c,d;
	for(;;){
		c=b;d=b*b;
		int o=cmp(d,a);
		if(o==1)b=b-(d-a)/(b+b);
		else if(o==-1)b=b+(a-d)/(b+b);
		else break;
		if(cmp(b,c)==0)break;
	}
	return b-num(1);
}
int main(){
}
