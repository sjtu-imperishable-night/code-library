struct L3{
	P3 s,t;
	L3(P3 s=P3(),P3 t=P3()):s(s),t(t){}
	void in(){s.in();t.in();}
	D length()const{return dis(s,t);}
};
bool threepoint_on_line(P3 a,P3 b,P3 c){//判断三点共线
	return !sgn(cj(a-b,b-c).norm());
}
bool point_on_line(P3 a,L3 b){//点是否在直线上
	return !sgn(cj(a-b.s,b.t-b.s).norm());
}
bool point_on_segment(P3 a,L3 b){//点是否在线段上
	return !sgn(cj(a-b.s,b.t-b.s).norm())&&sgn(dj(b.s-a,b.t-a))<=0;
}
bool two_side(P3 a,P3 b,L3 c){//两点是否再直线两边
	return sgn(dj(cj(a-c.s,c.t-c.s),cj(b-c.s,c.t-c.s)))<0;
}
bool segment_intersect_judge(L3 a,L3 b){//判断两线段是否相交
	if(point_on_segment(b.s,a)||point_on_segment(b.t,a))return 1;
	if(point_on_segment(a.s,b)||point_on_segment(a.t,b))return 1;
	return two_side(a.s,a.t,b)&&two_side(b.s,b.t,a);
}
P3 line_intersect(L3 a,L3 b){//两直线交点，必须保证共面且不平行 
	P3 p=a.s;
	D t=((a.s.x-b.s.x)*(b.s.y-b.t.y)-(a.s.y-b.s.y)*(b.s.x-b.t.x))/(a.s.x-a.t.x)*(b.s.y-b.t.y)-(a.s.y-a.t.y)*(b.s.x-b.t.x);
	return a.s+(a.t-a.s)*t;
}
D point_to_line(P3 a,L3 b){//点到直线距离
	return cj(b.t-b.s,a-b.s).norm()/dis(b.s,b.t);
}
P3 project_to_line(P3 a,L3 b){//点在直线上投影
	return b.s+(b.t-b.s)*(dj(a-b.s,b.t-b.s)/(b.t-b.s).norm2());
}
P3 duichen(P3 a,L3 b){//点A关于直线B对称点
	P3 c=project_to_line(a,b);
	return c*2-a;
}
D point_to_segment(P3 a,L3 b){//点到线段距离
	if(sgn(dj(b.s-a,b.t-b.s)*dj(b.t-a,b.t-b.s))<=0)return point_to_line(a,b);
	return min(dis(a,b.s),dis(a,b.t));
}
D line_angle_cos(L3 a,L3 b){//两直线夹角的cos 
	return dj(a.t-a.s,b.t-b.s)/a.length()/b.length();
}
