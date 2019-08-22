D volume4(P3 a,P3 b,P3 c,P3 d){//已知四点，利用混合积 
	return hhj(b-a,c-a,d-a)/6;
}
D volume4(D l,D n,D a,D m,D b,D c){//已知六边长求体积 
	D x,y;
	l*=l;n*=n;a*=a;m*=m;b*=b;c*=c;
	x=4*a*b*c-a*(b+c-m)*(b+c-m)-b*(c+a-n)*(c+a-n);
	y=c*(a+b-l)*(a+b-l)-(a+b-l)*(b+c-m)*(c+a-n);
	return (sqrt(x-y)/12);
}
P3 neixin(P3 a,P3 b,P3 c,P3 d){//四面体内心 
	D sa=area(b,c,d),sb=area(a,c,d),sc=area(a,b,d),sd=area(a,b,c);
	return P3(sa*a.x+sb*b.x+sc*c.x+sd*d.x,sa*a.y+sb*b.y+sc*c.y+sd*d.y,sa*a.z+sb*b.z+sc*c.z+sd*d.z)/(sa+sb+sc+sd);
}
