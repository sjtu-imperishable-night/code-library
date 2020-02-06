int l,r,w,m1,m2,an=0;
for(;l<=r;){
	w=(r-l)/3;m1=l+w;m2=r-w;
	if(f(m1)>f(m2))r=m2-1,an=max(an,f(m1));
	else l=m1+1,an=max(an,f(m2));
}
