#include<bits/stdc++.h>
#define N 111111
#define S 999983
#define M 998244353
#define LL long long
using namespace std;
LL pw[N],V[N];
int n,i,rk[N],sa[N],h[N];
char s[N];
LL cal(int L,int R){return (V[R]-V[L-1]*pw[R-L+1]%M+M)%M;}
bool ok(int i,int j,int l){return cal(i,i+l-1)==cal(j,j+l-1);}
int lcp(int i,int j){
	int an=0,l=1,r=n+1-max(i,j),md;
	for(;l<=r;)if(ok(i,j,md=l+r>>1))an=md,l=md+1;else r=md-1;
	return an;
}
bool cmp(int i,int j){
	int z=lcp(i,j);
	return s[i+z]<s[j+z];
}
int main(){
	scanf("%s",s+1);n=strlen(s+1);
	for(pw[0]=i=1;i<=n;i++)pw[i]=pw[i-1]*S%M,sa[i]=i;
	for(i=1;i<=n;i++)V[i]=(V[i-1]*S+s[i]-'a'+1)%M;
	sort(sa+1,sa+n+1,cmp);
	for(i=1;i<=n;i++)rk[sa[i]]=i;
	for(i=1;i<=n;i++)printf("%d%c",sa[i],i==n?'\n':' ');
	for(i=2;i<=n;i++)h[i]=lcp(sa[i-1],sa[i]);
}