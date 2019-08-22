double cal(double v){
	for(int i=1;i<=m;i++)p[i]=P{X[i],Y[i],W[i]-C[i]*v};
	//MST
	return an;
}
double ratio_mst(){
	double L=0,R=1e9,md;
	for(int i=1;i<=60;i++)
		if(cal(md=(L+R)/2)<0)R=md;else L=md;
	return md;
}
