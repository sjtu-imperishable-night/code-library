D polygon_area(vector<P> a){
	D an=0.0;int n=(int)a.size();
	for(int i=0;i<n;i++)an+=cj(a[i],a[(i+1)%n])*0.5;
	return an;
}
