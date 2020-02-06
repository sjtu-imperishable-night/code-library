P zhongxin(P a,P b,P c){//重心
	return P((a.x+b.x+c.x)/3.0,(a.y+b.y+c.y)/3.0);
}
P neixin(P a,P b,P c){//内心
	D p=dis(a,b)+dis(b,c)+dis(c,a);
	return (a*dis(b,c)+b*dis(c,a)+c*dis(a,b))/p;
}
P waixin(P a,P b,P c){//外心
	P p=b-a,q=c-a,s(p.norm2()/2,q.norm2()/2);
	D d=cj(p,q);
	return a+P(cj(s,P(p.y,q.y)),cj(P(p.x,q.x),s))/d;
}
P chuixin(P a,P b,P c){//垂心
	return a+b+c-waixin(a,b,c)*2.0;
}
P fermat_point(P a,P b,P c){//费马点，到三个点距离之和最小的点
	if(a==b)return a;
	if(b==c)return b;
	if(c==a)return c;
	D ab=dis(a,b),bc=dis(b,c),ca=dis(c,a);
	D cosa=dj(b-a,c-a)/ab/ca,cosb=dj(a-b,c-b)/ab/bc,cosc=dj(b-c,a-c)/ca/bc;
	D sq3=pi/3.0;
	P md;
	if(sgn(cosa+0.5)<0)md=a;
	else if(sgn(cosb+0.5)<0)md=b;
	else if(sgn(cosc+0.5)<0)md=c;
	else if(sgn(dj(b-a,c-a))<0)md=line_intersect(L(a,b+(c-b).rotate(sq3)),L(b,c+(a-c).rotate(sq3)));
	else md=line_intersect(L(a,c+(b-c).rotate(sq3)),L(c,b+(a-b).rotate(sq3)));
	return md;
}
