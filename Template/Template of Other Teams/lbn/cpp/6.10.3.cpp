struct S3{//可以表示一个平面或者空间里一个三角形 
	P3 a,b,c;
	S3(P3 a=P3(),P3 b=P3(),P3 c=P3()):a(a),b(b),c(c){}
	void in(){a.in();b.in();c.in();}
	P3 base(){return cj(a-b,b-c);}//法向量
};
bool point_on_plane(P3 a,S3 b){//判断点是否在平面上 
	return !sgn(dj(b.base(),a-b.a));
}
bool two_side(P3 a,P3 b,S3 c){//判断两点是否在平面异侧
	return sgn(dj(c.base(),a-c.a)*dj(c.base(),b-c.a))<0;
}
bool plane_parallel(S3 a,S3 b){//判断两平面是否平行
	return !sgn(cj(a.base(),b.base()).norm());
}
bool line_plane_parallel(L3 a,S3 b){//判断直线与平面是否平行
	return !sgn(dj(a.t-a.s,b.base())); 
}
bool plane_vertical(S3 a,S3 b){//判断两平面是否垂直
	return !sgn(dj(a.base(),b.base())); 
}
bool line_plane_vertical(L3 a,S3 b){//判断直线与平面是否垂直
	return !sgn(cj(a.t-a.s,b.base()).norm()); 
}
P3 line_plane_intersect(L3 a,S3 b){//直线与平面交点 
	P3 p=b.base();
	D t=dj(p,b.a-a.s)/dj(p,a.t-a.s);
	return a.s+(a.t-a.s)*t;
}
L3 plane_intersect(S3 a,S3 b){//两平面交线，要保证不平行
	return L3(line_plane_intersect(line_plane_parallel(L3(a.a,a.b),b)?L3(a.b,a.c):L3(a.a,a.b),b),
	line_plane_intersect(line_plane_parallel(L3(a.c,a.a),b)?L3(a.b,a.c):L3(a.c,a.a),b));
}
D point_to_plane(P3 a,S3 b){//点到平面距离
	return fabs(dj(b.base(),a-b.a)/b.base().norm()); 
}
D plane_angle_cos(S3 a,S3 b){//面面角 
	P3 A=a.base(),B=b.base();
	return dj(A,B)/A.norm()/B.norm();
}
D line_plane_angle_sin(L3 a,S3 b){//线面角 
	P3 A=a.t-a.s,B=b.base(); 
	return dj(A,B)/A.norm()/B.norm();
}
