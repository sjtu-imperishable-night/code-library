struct C{//圆类
	P c;D r;
	explicit C(P c=P(),D r=0):c(c),r(r){}
	void in(){c.in();scanf("%lf",&r);}
};
bool operator==(C a,C b){
	return a.c==b.c&&cmp(a.r,b.r)==0;
}
bool operator!=(C a,C b){return !(a==b);}
bool in_circle(P a,C b){//点是否再圆内
	return cmp(dis(a,b.c),b.r)<=0;
}
int circle_relationship(C a,C b){//两圆关系
	if(a==b)return 0;//相同
	D d=dis(a.c,b.c),r1=a.r+b.r,r2=fabs(a.r-b.r);
	if(sgn(d-r1)==1)return 5;//相离
	if(sgn(d-r1)==0)return 4;//外切
	if(sgn(d-r2)==1)return 3;//相交
	if(sgn(d-r2)==0)return 2;//内切
	return 1;//相含
}
C make_circle(P a,P b){//以两点为直径做圆
	return C((a+b)/2,dis(a,b)/2);
}
C make_circle(P a,P b,P c){//求经过三个点的圆
	P p=waixin(a,b,c);
	return C(p,dis(p,a));
}
void line_circle_intersect(L a,C b,P&p1,P&p2){//直线与圆交
	D x=sqrt(sqr(b.r)-sqr(point_to_line(b.c,a)));
	p1=project_to_line(b.c,a)+(a.s-a.t).unit()*x;
	p2=project_to_line(b.c,a)-(a.s-a.t).unit()*x;
}
P __circle_intersect(C a,C b){
	P r=(b.c-a.c).unit();
	D d=dis(a.c,b.c);
	D x=0.5*((sqr(a.r)-sqr(b.r))/d+d);
	D h=sqrt(sqr(a.r)-sqr(x));
	return a.c+r*x+r.rot90()*h;
}
void circle_intersect(C a,C b,P&p1,P&p2){//两圆的交点 
	p1=__circle_intersect(b,a);
	p2=__circle_intersect(a,b);
}
bool tanCP(C c,P a,P&p1,P&p2){//求点和圆的切点，按关于点的顺时针方向返回两个点
	D x=(a-c.c).norm2(),d=x-sqr(c.r);
	if(sgn(d)<=0)return 0;//点在圆上没有切点
	P p=(a-c.c)*sqr(c.r)/x,o=((c.c-a)*c.r*sqrt(d)/x).rot90();
	p1=c.c+p+o;p2=c.c+p-o;return 1;
}
void tangent(P a,C b,L&l1,L&l2){//过一点关于圆的切线 
	C p=make_circle(a,b.c);
	P d1,d2;
	circle_intersect(p,b,d1,d2);
	l1=L(d1,a);l2=L(d2,a);
}
bool extan(C a,C b,L&l1,L&l2){//求两圆的外公切线，按a.o的顺时针方向返回两条线
	if(sgn(a.r-b.r)==0){
		P c=b.c-a.c;
		c=(c.unit()*a.r).rot90();
		l1=L(a.c+c,b.c+c);l2=L(a.c-c,b.c-c);
		return 1;
	}else{
		P p=(b.c*a.r-a.c*b.r)/(a.r-b.r),p1,p2,q1,q2;
		if(tanCP(a,p,p1,p2)&&tanCP(b,p,q1,q2)){
			if(a.r<b.r)swap(p1,p2),swap(q1,q2);
			l1=L(p1,q1);l2=L(p2,q2);
			return 1;
		}else return 0;
	}
}
bool intan(C a,C b,L&l1,L&l2){//求两圆的内共切线，按a.o的顺时针方向返回两条线
	P p=(a.c*b.r+b.c*a.r)/(a.r+b.r),p1,p2,q1,q2;
	if(tanCP(a,p,p1,p2)&&tanCP(b,p,q1,q2)){
		l1=L(p1,q1);l2=L(p2,q2);
		return 1;
	}else return 0;
}
D circle_intersect_area(C a,C b){//两圆相交的面积
	D d=(a.c-b.c).norm();
	if(sgn(d-(a.r+b.r))>=0)return 0;
	if(sgn(d-abs(a.r-b.r))<=0){
		D r=min(a.r,b.r);
		return r*r*pi;		
	}
	D x=(d*d+a.r*a.r-b.r*b.r)/(d*2),t1=acos(min(1.,max(-1.,x/a.r))),t2=acos(min(1.,max(-1.,(d-x)/b.r)));
	return a.r*a.r+t1+b.r*b.r*t2-d*a.r*sin(t1);
}
D SectorArea(C c,P a,P b){//不大于180度的扇形面积
	D u=(c.c-a).norm2(),v=(c.c-b).norm2(),w=(a-b).norm2();
	return sqr(c.r)*acos((u+v-w)*.5/sqrt(u)/sqrt(v))*.5;
}
