#include<bits/stdc++.h>//普通平衡树
#define N 511111
#define M 33333333
#define rd(x) scanf("%d",&x)
using namespace std;
int id,pre,suc,an,T[N],sz[M],L[M],R[M],v[M];
void ps(int x){sz[x]=sz[L[x]]+sz[R[x]]+1;}
int Copy(int x){
	id++;sz[id]=sz[x];L[id]=L[x];R[id]=R[x];
	v[id]=v[x];return id;
}
int newv(int z){
	id++;v[id]=z;sz[id]=1;return id;
}
int RD(){
	return (rand()%32768)*32768+(rand()%32768);
}
int merge(int x,int y){
	if(!x||!y)return x+y;int z;
	int o=RD()%(sz[x]+sz[y]);
	if(o<sz[x])z=Copy(y),L[z]=merge(x,L[y]);
	else z=Copy(x),R[z]=merge(R[x],y);
	ps(z);return z;
}
void split(int x,int&y,int&z,int k){
	y=z=0;if(!x)return;
	if(sz[L[x]]>=k)z=Copy(x),split(L[x],y,L[z],k),ps(z);
	else y=Copy(x),split(R[x],R[y],z,k-sz[L[x]]-1),ps(y);
}
void getrk(int x,int z){
	if(!x)return;
	if(z<=v[x])getrk(L[x],z);else
	an+=sz[L[x]]+1,getrk(R[x],z);
}
int calrk(int x,int z){
	an=1;
	getrk(x,z);
	return an;
}
int kth(int x,int z){
	if(z==sz[L[x]]+1)return v[x];
	return z<=sz[L[x]]?kth(L[x],z):kth(R[x],z-sz[L[x]]-1);
}

int ins(int nv,int z){
	int A,B,rk=calrk(nv,z);
	split(nv,A,B,rk-1);
	return merge(merge(A,newv(z)),B);
}
int del(int nv,int z){
	int A,B,C,D,rk=calrk(nv,z);
	split(nv,A,C,rk-1);
	split(C,D,B,1);
	if(v[D]!=z)return nv;
	return merge(A,B);
}
void fdpre(int x,int z){
	if(!x)return;
	if(v[x]<=z){
		pre=max(pre,v[x]);
		fdpre(R[x],z);
	}else fdpre(L[x],z);
}
void fdsuc(int x,int z){
	if(!x)return;
	if(v[x]>=z){
		suc=min(suc,v[x]);
		fdsuc(L[x],z);
	}else fdsuc(R[x],z);
}
int main(){
	srand(23333);
	int n,la,op,x;
	rd(n);
	for(int i=1;i<=n;i++){
		rd(la);rd(op);rd(x);
		if(op==1){//add x
			T[i]=ins(T[la],x);
		}
		if(op==2){//del x  没有不删
			T[i]=del(T[la],x);
		}
		if(op==3){//fd rank
			T[i]=T[la];
			printf("%d\n",calrk(T[i],x));
		}
		if(op==4){//fd rkx=?
			T[i]=T[la];
			printf("%d\n",kth(T[i],x));
		}
		if(op==5){//fd pre
			T[i]=T[la];pre=-2147483647;
			fdpre(T[i],x-1);
			printf("%d\n",pre);
		}
		if(op==6){//fd suc
			T[i]=T[la];suc=2147483647;
			fdsuc(T[i],x+1);
			printf("%d\n",suc);
			
		}
	}
}
