#include<bits/stdc++.h>
#define N 300006
using namespace std;
char s[N];int i,q,p,n,id,cnt[N],num[N],F[N],len[N],c[N][26];
void add(int z,int n){//注意这里的n是目前添加的字符数 
	while(s[n-len[p]-1]!=s[n])p=F[p];//失配后找一个尽量最长的
	if(!c[p][z]){//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
		int q=++id,k=F[p];//新建节点
		len[q]=len[p]+2;
		while(s[n-len[k]-1]!=s[n])k=F[k];//构建失败指针
		F[q]=c[k][z];c[p][z]=q;num[q]=num[F[q]]+1;
	}
	p=c[p][z];cnt[p]++;//统计该类回文出现次数，这里的p即为last，这是简化写法 
}
int main(){
    id=1;F[0]=F[1]=1;len[1]=-1;//开头放一个字符集中没有的字符，减少特判
    scanf("%s",s+1);n=strlen(s+1);for(i=1;i<=n;i++)add(s[i]-'a',i);
    for(i=id;i;i--)cnt[F[i]]+=cnt[i];//父亲累加儿子的cnt 
}
