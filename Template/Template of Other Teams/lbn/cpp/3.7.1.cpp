#include<bits/stdc++.h>
#define N 222222//注意N开两倍
char s[N];
int n,i,x,p,q,np,nq,cnt,L,st[N],c[N][26],F[N],pos[N],bl[N],to[N],b[N],sz[N];
void add(int x){//在后面加入一个字符x
	p=np;st[np=++cnt]=st[p]+1;to[np]=i;pos[i]=np;
	for(;p&&!c[p][x];p=F[p])c[p][x]=np;
	if(!p)F[np]=1;else 
	if(st[p]+1==st[q=c[p][x]])F[np]=q;else{
		st[nq=++cnt]=st[p]+1;memcpy(c[nq],c[q],sizeof c[q]);
		F[nq]=F[q];F[q]=F[np]=nq;
		for(;p&&c[p][x]==q;p=F[p])c[p][x]=nq;
	}
}
int main(){
	np=cnt=1;scanf("%s",s);n=strlen(s);//注意根为1
	for(i=0;i<n;i++)add(s[i]-'a');
	for(i=1;i<=cnt;i++)b[st[i]]++;//基数排序求RIGHT集合 
	for(i=1;i<=n;i++)b[i]+=b[i-1];
	for(i=1;i<=cnt;i++)bl[b[st[i]]--]=i;
	for(i=0,p=1;i<n;i++)sz[p=c[p][s[i]-'a']]++;
	for(i=cnt;i;i--)sz[F[bl[i]]]+=sz[bl[i]];
	//for(i=0;i<n;i++)printf("%d ",sz[pos[i]]);//RIGHT集合大小
	scanf("%s",s),n=strlen(s);
	for(p=1,L=i=0;i<n;i++)//B串在A串上跑得到当前匹配
        	if(c[p][x=s[i]-'a'])p=c[p][x],L++;else{//p为在后缀机上的点
			for(;!c[p][x]&&p;p=F[p]);
			if(!p)p=1,L=0;else L=st[p]+1,p=c[p][x];//L为当前匹配长度
		}
}
