#include<bits/stdc++.h>//O(klgm)
typedef long long LL;using namespace std;
const int M=1e9+7,N=1e6+10;LL res[N],pw[N],cc[N];int n,k,i;
LL Pw(LL a,LL b,LL p){LL v=1;for(a%=p;b;a=a*a%p,b>>=1)if(b&1)v=v*a%p;return v;}
int main(){
	scanf("%d%d",&n,&k);
	for(pw[0]=1,i=1;i<N;i++)pw[i]=pw[i-1]*i%M;
	for(i=1;i<k+5;i++)res[i]=(res[i-1]+Pw(i,k,M))%M;
	if(n<=k+4)return printf("%I64d",res[n]),0;
	for(i=1;i<k+5;i++){
		cc[i]=Pw(pw[i-1]*pw[k+4-i],M-2,M)*res[i]%M;
		if((k+4-i)&1)cc[i]=(M-cc[i])%M;
	}
	LL an=0,p=1;
	for(i=1;i<k+5;i++)p=p*(n-i)%M;
	for(i=1;i<k+5;i++)an=(an+p*Pw(n-i,M-2,M)%M*cc[i])%M;
	printf("%I64d",an);
}
