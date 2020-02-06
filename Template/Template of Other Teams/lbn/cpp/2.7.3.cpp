namespace Left_Tree{//可持久化左偏树
	struct P{int l,r,x,h;LL v;}T[N*40];
	int RT[N],num;
	int New(P o){T[++num]=o;return num;}
	void init(){num=0;T[0].l=T[0].r=T[0].x=T[0].h=0;T[0].v=INF;}
	int mg(int x,int y){
		if(!x)return y;
		if(T[x].v>T[y].v)swap(x,y);
		int o=New(T[x]);
		T[o].r=mg(T[o].r,y);
		if(T[T[o].l].h<T[T[o].r].h)swap(T[o].l,T[o].r);
		T[o].h=T[T[o].r].h+1;
		return o;
	}
	void add(int &k,LL v,int x){int o=New(T[0]);T[o].v=v,T[o].x=x;k=mg(k,o);}
}
using namespace Left_Tree;
