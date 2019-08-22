#include<bits/stdc++.h>//NOI2005维修数列
const int oo=2e9,BS=700,MN=5e5+10,MB=MN/BS*2+1000;
using namespace std;
int data[MB][BS],sz[MB],sav[MB],totsum[MB],sidemax[MB][2],maxsum[MB],fList[MB],ne[MB],pos;
bool same[MB],rev[MB];
int newnode(){return fList[++pos];}
void delnode(int t){fList[pos--]=t;}
void find(int &p,int &b){for(b=0;p>sz[b];b=ne[b])p-=sz[b];}//找到所在的块 
void maintainblock(int b){//重新制作块 
	if(same[b]){//有相同标记 
		totsum[b]=sav[b]*sz[b];
		if(sav[b]>0)maxsum[b]=totsum[b];else maxsum[b]=sav[b];
		sidemax[b][0]=sidemax[b][1]=maxsum[b];
	}else{//没有相同标记 
		totsum[b]=0;maxsum[b]=-oo;
		for(int last=0,i=sz[b]-1;i>=0;--i){//中间最大的一段 
			totsum[b]+=data[b][i];last+=data[b][i];
			if(maxsum[b]<last)maxsum[b]=last;
			if(last<0)last=0;
		}
		sidemax[b][0]=-oo;
		for(int last=0,i=0;i<sz[b];++i){//左边起最大的一段 
			last+=data[b][i];
			if(sidemax[b][0]<last)sidemax[b][0]=last;
		}
		sidemax[b][1]=-oo;
		for(int last=0,i=sz[b]-1;i>=0;--i){//右边起最大的一段 
			last+=data[b][i];
			if(sidemax[b][1]<last)sidemax[b][1]=last;
		}
	}
}
void rever(int b){//翻转 
	if(b==-1||!rev[b])return;rev[b]=0;if(same[b])return;
	for(int l=0,r=sz[b]-1;l<r;++l,--r)swap(data[b][l],data[b][r]);
	swap(sidemax[b][0],sidemax[b][1]);
}
void maintainlist(int b){//将b以后的碎块合并 
	for(bool x=0;b!=-1;b=ne[b],x=0){
		for(int t=ne[b];t!=-1&&sz[b]+sz[t]<=BS;t=ne[b],x=true){
			if(!(same[b]&&same[t]&&sav[b]==sav[t])){
				rever(b);rever(t);
				if(same[b])for(int i=0;i<sz[b];++i)data[b][i]=sav[b];
				for(int i=0;i<sz[t];++i)data[b][sz[b]+i]=same[t]?sav[t]:data[t][i];
				same[b]=0;
			}
			sz[b]+=sz[t];ne[b]=ne[t];delnode(t);
		}
		if(x)maintainblock(b);
	}
}
void fillblock(int b,int sv,int n,int e){//维护一个值相同块的信息 
	same[b]=true;sav[b]=sv;ne[b]=e;
	sz[b]=n;rev[b]=0;maintainblock(b);
}
void fillblock(int b,int str[],int n,int e){//维护一个块的信息 
	same[b]=rev[b]=0;sz[b]=n;ne[b]=e;
	memcpy(data[b],str,n*sizeof(int));maintainblock(b);
}
void splite(int b,int p){//将块b从p处断开 
	if(b==-1||sz[b]==p)return;
	int t=newnode();rever(b);
	if(same[b])fillblock(t,sav[b],sz[b]-p,ne[b]);else fillblock(t,data[b]+p,sz[b]-p,ne[b]);
	ne[b]=t;sz[b]=p;maintainblock(b);
}
void ins(int p,int n,int str[]){//插入 
	int b,i,t;find(p,b);splite(b,p);
	for(i=0;i+BS<=n;i+=BS){
		t=newnode();fillblock(t,str+i,BS,ne[b]);
		ne[b]=t;b=t;
	}
	if(n-i){fillblock(t=newnode(),str+i,n-i,ne[b]);ne[b]=t;}
	maintainlist(ne[b]);
}
void erase(int p,int n){//删除 
	int b,e;find(p,b);splite(b,p);
	for(e=ne[b];n>sz[e];e=ne[e])n-=sz[e];
	splite(e,n);e=ne[e];
	for(int t=ne[b];t!=e;t=ne[b])ne[b]=ne[t],delnode(t);
}
int List[MB];
void reverse(int p,int n){//翻转 
	int b,e,i,t;find(p,b);splite(b,p);
	for(e=ne[b];n>sz[e];e=ne[e])n-=sz[e];
	splite(e,n);e=ne[e];
	for(i=0,t=ne[b];t!=e;t=ne[t],++i)List[i]=t;
	ne[b]=List[--i];
	for(;i>=0;--i){
		ne[List[i]]=i?List[i-1]:t;
		rev[List[i]]=!rev[List[i]];
	}
	maintainlist(b);
}
void makesame(int p,int n,int v){//相同值 
	int b,t;find(p,b);splite(b,p);
	for(t=ne[b];n>sz[t];n-=sz[t],t=ne[t])fillblock(t,v,sz[t],ne[t]);
	if(n)splite(t,n),fillblock(t,v,n,ne[t]);
	maintainlist(b);
}
int getsum_in_block(int b,int p,int n){//块中总和 
	int sum,l,r;if(same[b])return sav[b]*n;
	if(rev[b]){l=sz[b]-p-n;r=sz[b]-p-1;}else{l=p;r=p+n-1;}
	for(sum=0;l<=r;++l)sum+=data[b][l];
	return sum;
}
void getsum(int p,int n){//总和 
	int b,t,sum,i;find(p,b);
	sum=getsum_in_block(b,p,min(n,sz[b]-p));n-=min(n,sz[b]-p);
	for(t=ne[b]; n>sz[t]; t=ne[t])sum+=totsum[t],n-=sz[t];
	sum+=getsum_in_block(t,0,n);
	printf("%d\n",sum);
}
void getmaxsum(){//最大区间和 
	int res=-oo,last=0;
	for(int b=0; b!=-1; b=ne[b]){
		res=max(max(res,last+sidemax[b][rev[b]]),maxsum[b]);
		last=max(max(last+totsum[b],sidemax[b][!rev[b]]),0);
	}
	printf("%d\n",res);
}
int main(){
	int n,T,i,p,v,a[MN];char order[99];
	for(int i=1;i<MB;++i)fList[i]=i;ne[0]=-1;
	scanf("%d%d",&n,&T);for(i=0;i<n;++i)scanf("%d",a+i);
	ins(0,n,a);
	while(T--){
		scanf("%s",order);
		if(order[2]=='X')getmaxsum();
		else switch(order[0]){
			case 'I':scanf("%d%d",&p,&n);for(i=0;i<n;++i)scanf("%d",a+i);ins(p,n,a);break;
			case 'D':scanf("%d%d",&p,&n);erase(p-1, n);break;
			case 'M':scanf("%d%d%d",&p,&n,&v);makesame(p-1, n ,v);break;
			case 'R':scanf("%d%d",&p,&n);reverse(p-1,n);break;
			case 'G':scanf("%d%d",&p,&n);getsum(p-1,n);break;
		}
	}
}
