double l,r,w,m1,m2,v1,v2;
for(;r-l>eps;){
	w=(r-l)/3;
	m1=l+w;m2=r-w;
	v1=f(m1);v2=f(m2);
	if(v1>v2)r=m2;else l=m1;
}