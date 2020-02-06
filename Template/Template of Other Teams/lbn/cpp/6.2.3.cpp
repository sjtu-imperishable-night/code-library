struct L{//一个线段或者直线
	P s,t;
	L(P s=P(),P t=P()):s(s),t(t){}
	void in(){scanf("%lf%lf%lf%lf",&s.x,&s.y,&t.x,&t.y);}
	void out(){printf("%.6f %.6f --> %.6f %.6f\n",s.x,s.y,t.x,t.y);}
	D length()const{return dis(s,t);}
};
bool point_on_line(P a,L b){//点是否在直线上
	return !sgn(cj(a-b.s,b.t-b.s));
}
bool point_on_segment(P a,L b){//点是否在线段上
	return !sgn(cj(a-b.s,b.t-b.s))&&sgn(dj(b.s-a,b.t-a))<=0;
}
bool two_side(P a,P b,L c){//两点是否再直线两边
	return sgn(cj(a-c.s,c.t-c.s))*sgn(cj(b-c.s,c.t-c.s))<0;
}
bool segment_intersect_judge(L a,L b){//判断两线段是否相交
	if(point_on_segment(b.s,a)||point_on_segment(b.t,a))return 1;
	if(point_on_segment(a.s,b)||point_on_segment(a.t,b))return 1;
	return two_side(a.s,a.t,b)&&two_side(b.s,b.t,a);
}
P line_intersect(L a,L b){//直线相交
	D s1=cj(a.t-a.s,b.s-a.s),s2=cj(a.t-a.s,b.t-a.s);
	return (b.s*s2-b.t*s1)/(s2-s1);
}
D point_to_line(P a,L b){//点到直线距离
	return fabs(cj(b.t-b.s,a-b.s))/dis(b.s,b.t);
}
P project_to_line(P a,L b){//点在直线上投影
	return b.s+(b.t-b.s)*(dj(a-b.s,b.t-b.s)/(b.t-b.s).norm2());
}
P duichen(P a,L b){//点A关于直线B对称点
	P c=project_to_line(a,b);
	return P(c.x*2-a.x,c.y*2-a.y);
}
D point_to_segment(P a,L b){//点到线段距离
	if(sgn(dj(b.s-a,b.t-b.s)*dj(b.t-a,b.t-b.s))<=0)
		return point_to_line(a,b);
	return min(dis(a,b.s),dis(a,b.t));
}
D angle_cos(L a,L b){//两直线夹角的cos 
	return dj(a.t-a.s,b.t-b.s)/a.length()/b.length();
}
