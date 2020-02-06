#include<bits/stdc++.h>
#define N 1111
#define M 111111
#define CL(a) memset(a,0,sizeof(a))
using namespace std;
struct SPFA{
	int h,t,tot,q[N],fir[N],la[M],ne[M],va[M],d[N];bool v[N];
   	void in(){tot=0;memset(d,63,sizeof d);CL(v);CL(fir);}
   	void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
   	void work(int S,int n){//给定起点S和总点数n，方便循环队列
   	    int i,x,y;
   	    for(h=d[q[t=1]=S]=0;h^t;)
   	        for(i=fir[x=q[h=h%n+1]],v[x]=0;i;i=ne[i])
   	            if(d[x]+va[i]<d[y=la[i]])if(d[y]=d[x]+va[i],!v[y])v[q[t=t%n+1]=y]=1;
   	}
}A;
struct Kshort{
	int tot,n,m,S,T,k,fir[N],cnt[N],va[M],la[M],ne[M];
	struct P{//用当前代价+估价比较大小
		int x,z;P(){}
		P(int x,int z):x(x),z(z){}
		bool operator<(P a)const{return a.z+A.d[a.x]<z+A.d[x];}
	};
	priority_queue<P>Q;
	void in(){tot=0;CL(fir);CL(cnt);}
	void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
	void init(){
		int i,x,y,z;A.in();
		scanf("%d%d%d%d%d",&n,&m,&S,&T,&k);
		for(i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),A.ins(y,x,z),ins(x,y,z);
		A.work(T,n);
	}
	int work(){
		P o;int i;
		for(Q.push(P(S,0));!Q.empty();){
        	o=Q.top();Q.pop();
			++cnt[o.x];
			if(cnt[o.x]>k)continue;//该点已经进入超过k次，舍去
			if(o.x==T&&cnt[o.x]==k)return o.z;//终点已进队k次
			for(i=fir[o.x];i;i=ne[i])Q.push(P(la[i],o.z+va[i]));//扩展答案
    	}
		return -1;
	}
}G;
int main(){
	G.init();
	printf("%d\n",G.work());
}
