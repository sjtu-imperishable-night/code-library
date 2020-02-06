#include<bits/stdc++.h>
#define CL(a) memset(a,0,sizeof a)
#define N 111111
int n,i,sa[N],rk[N],h[N];char s[N];
int cmp(int *r,int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}
//用于比较第一关键字与第二关键字,比较特殊的地方是,预处理的时候,r[n]=0(小于前面出现过的字符)
void SA(char*s,int*sa,int*rk,int*h,int n,int m){
	static int V[N],W[N],b[N];int i,j,k,p;CL(V);
	for(i=1;i<=n;i++)V[rk[i]=s[i]]++;
	for(i=1;i<=m;i++)V[i]+=V[i-1];
	for(i=n;i;i--)sa[V[rk[i]]--]=i;
	for(k=1;k<=n;k<<=1,m=p){//通过已经求出的长度J的SA，来求2*J的SA
		for(p=0,i=n;i>n-k;i--)b[++p]=i;//特殊处理没有第二关键字的
		for(i=1;i<=n;i++)if(sa[i]>k)b[++p]=sa[i]-k;//利用长度J的，按第二关键字排序
		for(CL(V),i=1;i<=n;i++)V[rk[b[i]]]++;
		for(i=1;i<=m;i++)V[i]+=V[i-1];
		for(i=n;i;i--)sa[V[rk[b[i]]]--]=b[i];//基数排序部分
		for(i=1;i<=n;i++)b[i]=rk[i];
		for(rk[sa[1]]=p=1,i=2;i<=n;i++)//更新名次数组rk[],注意判定相同的
			rk[sa[i]]=p+=b[sa[i]]^b[sa[i-1]]||b[sa[i]+k]^b[sa[i-1]+k];
	}
    for(i=1,k=0;i<=n;h[rk[i++]]=k)//利用单调性求height[]，合法范围2~n 
    	for(k?k--:0;s[i+k]==s[sa[rk[i]-1]+k];k++);
}
int main(){
	scanf("%s",s+1);n=strlen(s+1);
	SA(s,sa,rk,h,n,128);
}
