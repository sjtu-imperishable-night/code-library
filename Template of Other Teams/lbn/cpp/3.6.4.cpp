#include<bits/stdc++.h>
#define N 666666
int n,m,cnt,p,q,np,nq,i,j,k,tp,pos,sa[N],rk[N],C[N][26],c[N][26],F[N],st[N],to[N],h[N];char s[N];bool v[N];
void add(int w){
	for(p=np,st[np=++cnt]=st[p]+1,to[np]=i;p&&!c[p][w];p=F[p])c[p][w]=np;
	if(!p)F[np]=1;else if(st[q=c[p][w]]==st[p]+1)F[np]=q;
	else for(st[nq=++cnt]=st[p]+1,memcpy(c[nq],c[q],sizeof(c[q])),F[nq]=F[q],F[q]=F[np]=nq;p&&c[p][w]==q;p=F[p])c[p][w]=nq;
}
void dfs(int x){
	if(to[x])sa[++tp]=to[x];
	for(int i=0;i<26;i++)if(C[x][i])dfs(C[x][i]);
}
int main(){
	for(scanf("%s",s+1),n=strlen(s+1),np=++cnt,i=n;i;i--)add(s[i]-'a');
	for(v[1]=i=1;i<=cnt;i++)if(to[i])for(pos=n,j=i;!v[j];v[j]=1,j=F[j],pos--)pos-=st[j]-st[F[j]]-1,C[F[j]][s[pos]-'a']=j;
	for(dfs(1),i=1;i<=n;i++)rk[sa[i]]=i;
	for(i=1;i<=n;i++)printf("%d ",sa[i]);puts("");
	for(i=1;i<=n;h[rk[i++]]=k)for(k?k--:0,j=sa[rk[i]-1];s[i+k]==s[j+k];k++);
	for(i=2;i<=n;i++)printf("%d ",h[i]);
}
