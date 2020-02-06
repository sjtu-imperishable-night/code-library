D twopoint_circle_intersect(L a,C b,P&p1,P&p2){//直线与两点交及距离 
	D y=point_to_line(b.c,a);
	D x=sqrt(sqr(b.r)-sqr(y));
	p1=project_to_line(b.c,a)+(a.s-a.t).unit()*x;
	p2=project_to_line(b.c,a)-(a.s-a.t).unit()*x;
	return point_to_segment(b.c,a);
}
D circle_and_triangle(C c,P a,P b){//圆与一点在圆心的三角形交 
	if(sgn(cj(a-c.c,b-c.c))==0)return 0;
	bool f1=in_circle(a,c),f2=in_circle(b,c);
	P pa,pb; 
	L l=L(a,b);
	if(f1&&f2)return Area(a,b,c.c);//两点都在圆内
	D d=twopoint_circle_intersect(l,c,pa,pb);
	if(d>c.r-eps)return SectorArea(c,a,b);//两点都在圆外且两点的线段与圆无交
	if(f1)return Area(a,pb,c.c)+SectorArea(c,pb,b);//一点在圆内，一点在圆外
	if(f2)return Area(pa,b,c.c)+SectorArea(c,a,pa);
	return Area(pa,pb,c.c)+SectorArea(c,a,pa)+SectorArea(c,pb,b);//两点都在圆外且两点的线段与圆有交
}
D circle_and_polygon(C c,vector<P>a){//圆与多边形交
	int n=a.size(),i;D an=0;
	a.push_back(a[0]);//最后添一个方便处理
	for(i=0;i<n;i++){
		D d=circle_and_triangle(c,a[i],a[i+1]);//叉积判断正负
		if(cj(a[i]-c.c,a[i+1]-c.c)>0)an+=d;else an-=d;
	}
	return fabs(an);//返回正值
}
