typedef complex<D>CP;
vector<CP> equa3(D a,D b,D c,D d){
	vector<CP>AN;
	D k=b/a,m=c/a,n=d/a,p=-k*k/3.+m,q=2.*k*k*k/27-k*m/3.+n,dlt=q*q/4+p*p*p/27;
	static CP om[3]={CP(1,0),CP(-0.5,0.5*sqrt(3)),CP(-0.5,-0.5*sqrt(3))},r1,r2;
	if(dlt>0){
		r1=cbrt(-q/2.+sqrt(dlt));
		r2=cbrt(-q/2.-sqrt(dlt));
	}else{
		r1=pow(-q/2.+pow(CP(dlt),0.5),1./3);
		r2=pow(-q/2.-pow(CP(dlt),0.5),1./3);
	}
	for(int i=0;i<3;i++)AN.push_back(-k/3.+r1*om[i]+r2*om[i*2%3]);
	return AN;
}
