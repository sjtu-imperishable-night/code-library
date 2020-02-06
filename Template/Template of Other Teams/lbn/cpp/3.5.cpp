#include<bits/stdc++.h>
using namespace std;const int N=110010;
int n,i,ans,l,p,mx,r[N];char ma[N*2],s[N];
int main(){
	scanf("%s",s);n=strlen(s);ma[l++]='$';ma[l++]='#';
	for(i=0;i<n;i++)ma[l++]=s[i],ma[l++]='#';
	for(i=0;i<l;i++){
		r[i]=mx>i?min(r[2*p-i],mx-i):1;
		for(;ma[i+r[i]]==ma[i-r[i]];r[i]++);
		if(i+r[i]>mx)mx=i+r[i],p=i;
	}
	for(int i=0;i<2*n+2;i++)ans=max(ans,r[i]-1);
	printf("%d\n",ans);
}
