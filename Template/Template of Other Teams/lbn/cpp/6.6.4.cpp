struct Convex{//需传进来一个凸包，无重点，面积非空，pair<x,y>最小的点放在第一个,INF为坐标范围
	int n;
	vector<P>A,up,dw;
	Convex(vector<P>_A):A(_A){//预处理
		n=A.size();
		int p=0,i;
		for(i=1;i<n;i++)if(A[p]<A[i])p=i;
		for(i=0;i<=p;i++)dw.push_back(A[i]);
		for(i=p;i<n;i++)up.push_back(A[i]);
		up.push_back(A[0]);
	}
	void update(P p,int id,int&v0,int&v1){
		if(dj(A[v0]-p,A[id]-p)>0)v0=id;
		if(dj(A[v1]-p,A[id]-p)<0)v1=id;
	}
	void fd(int l,int r,P p,int&v0,int&v1){
		if(l==r)return;
		update(p,l%n,v0,v1);
		int sl=sgn(cj(A[l%n]-p,A[(l+1)%n]-p)),md,sm;
		for(;l+1<r;){
			md=l+r>>1;
			sm=sgn(cj(A[md%n]-p,A[(md+1)%n]-p));
			if(sm==sl)l=md;else r=md;
		}
		update(p,r%n,v0,v1);
	}
	bool contain(P p){//判断点p是否在凸包内（包括边界）
		if(p.x<dw[0].x||p.x>dw.back().x)return 0;
		int id=lower_bound(dw.begin(),dw.end(),P(p.x,-INF))-dw.begin();
		if(dw[id].x==p.x){
			if(dw[id].y>p.y)return 0;
		}else if(cj(dw[id-1]-p,dw[id]-p)<0)return 0;
		id=lower_bound(up.begin(),up.end(),P(p.x,INF),greater<P>())-up.begin();
		if(up[id].x==p.x){
			if(up[id].y<p.y)return 0;
		}else if(cj(up[id-1]-p,up[id]-p)<0)return 0;
		return 1;
	}
	bool get_tangent(P p,int&v0,int&v1){//求点p关于凸包的两个切点，如果在凸包外则有序返回编号，共线的多个切点任返一个
		if(contain(p))return 0;
		v0=v1=0;
		int id=lower_bound(dw.begin(),dw.end(),p)-up.begin(),VA=dw.size(),VB=up.size();
		fd(0,id,p,v0,v1);fd(id,VA,p,v0,v1);
		id=lower_bound(up.begin(),up.end(),p,greater<P>())-up.begin();
		fd(VA-1,VA-1+id,p,v0,v1);
		fd(VA-1+id,VA-1+VB,p,v0,v1);
		return 1;
	}
	pair<double,int>get_tangent(vector<P>&q,P e){
		int l=0,r=q.size()-2,md;
		for(;l+1<r;){
			md=l+r>>1;
			if(sgn(cj(q[md+1]-q[md],e))>0)r=md;else l=md;
		}
		return max(make_pair(dj(e,q[r]),r),make_pair(dj(e,q[0]),0));
	}
	int get_tangent(P e){//求凸包上和向量e叉积最大的点，返回编号，共线的多个切点返回任意一个
		pair<double,int>o=get_tangent(up,e);
		o.second=(o.second+(int)dw.size()-1)%n;
		o=max(o,get_tangent(dw,e));
		return o.second;	
	}
	int fd(P u,P v,int l,int r){
		int sl=sgn(cj(v-u,A[l%n]-u)),md,sm;
		for(;l+1<r;){
			md=(l+r)>>1;sm=sgn(cj(v-u,A[md%n]-u));
			if(sm==sl)l=md;else r=md;
		}
		return l%n;
	}
	bool intersection(P u,P v,int&v0,int&v1){//求凸包和直线u-v的交点，如果无严格相交返回0，有则返回(i,ne(i))的交点
		int p0=get_tangent(u-v),p1=get_tangent(v-u);
		if(sgn(cj(v-u,A[p0]-u))*sgn(cj(v-u,A[p1]-u))<0){
			if(p0>p1)swap(p0,p1);
			v0=fd(u,v,p0,p1);
			v1=fd(u,v,p1,p0+n);
			return 1;
		}else return 0;
	}
};
Convex A(convex_hull(a));//a为点集，调用convex_hull求凸包后传到A中
