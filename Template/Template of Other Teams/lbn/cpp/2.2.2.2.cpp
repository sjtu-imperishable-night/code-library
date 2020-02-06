int merge(int x,int y){//合并两个堆
	if(!x||!y)return x+y;
	if(V[x]<V[y])swap(x,y);
	R[x]=merge(R[x],y);
	F[R[x]]=x; 
	swap(L[x],R[x]);
	return x;
}
int init(int x){//新建一个单节点堆，返回编号
	V[++id]=x;
	L[id]=R[id]=F[id]=0;
}
void ins(int x,int z){//向编号为x的堆中插入一个权值为z的点
	return merge(x,init(z));
}
int top(int x){return V[x];}//返回堆顶值
int pop(int x){return merge(L[x],R[x]);}//删除堆顶，返回新的堆顶编号
