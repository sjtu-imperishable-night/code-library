#include<bits/stdc++.h>
#define N 111111
#define M 1000000007
#define pii pair<int,int>
#define fors(i)  for(auto i:e[x])if(i!=p)
using namespace std;
int ra[N];
int Pw(int a,int b,int p){
	int v=1;
	for(;b;b>>=1,a=1ll*a*a%p)if(b&1)v=1ll*v*a%p;
	return v;
}
int inv(int x,int p){return Pw(x,p-2,p);}
struct Sub{//子树类，存下面每个点的哈希值，最大和次大深度，以及对应哈希值
	vector<int>S;int d1,d2,H1,H2;
	Sub(){d1=d2=0;S.clear();}
	void add(int d,int v){//加入一个深度为d，哈希值为v的点
		S.push_back(v);
		if(d>d1)d2=d1,d1=d;else if(d>d2)d2=d;
	}
	int hash(){//哈希函数
		H1=H2=1;
		for(int i:S){
			H1=1ll*H1*(ra[d1]+i)%M;
			H2=1ll*H2*(ra[d2]+i)%M;
		}
		return H1;
	}
	pii del(int d,int v){//删除一个深度为d，哈希值为v的点
		if(d==d1)return {d2+1,1ll*H2*inv(ra[d2]+v,M)%M};
		return {d1+1,1ll*H1*inv(ra[d1]+v,M)%M};
	}
};
pii U[N];
int n,i,x,y,A[N];
Sub T[N];
vector<int>e[N];
void prepare(int n){//预处理
	for(int i=0;i<=n;i++)ra[i]=rand()%M;
}
void ins(int x,int y){e[x].push_back(y);}
void dfsD(int x,int p){//第一遍DFS，做顺着的，预处理，有根树O(n)
	T[x]=Sub();
	fors(i)dfsD(i,x),T[x].add(T[i].d1+1,T[i].H1);
	T[x].hash();
}
void dfsU(int x,int p){//第二遍DFS，A[x]求以x点为根的哈希值
	if(p)T[x].add(U[x].first,U[x].second);
	A[x]=T[x].hash();
	fors(i)U[i]=T[x].del(T[i].d1+1,T[i].H1),dfsU(i,x);
}
int main(){
	srand(23333);
	scanf("%d",&n);prepare(n);
	for(i=1;i<n;i++)scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	dfsD(1,0);dfsU(1,0);
	for(i=1;i<=n;i++)printf("%d\n",A[i]);
}
