C appollo(P a,P b,D k){//dis (a,o)*k=dis(b,o)
	C o;P A,B,p;
	D d=dis(a,b);
	p=(a-b).unit();
	B=b+p*d*k/(k+1.);
	A=b-p*d/(1.0/k-1.);
	return make_circle(A,B);
}