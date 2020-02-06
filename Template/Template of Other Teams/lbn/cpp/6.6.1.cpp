bool turn_left(P a,P b,P c){return sgn(cj(b-a,c-a))>=0;}
bool turn_right(P a,P b,P c){return sgn(cj(b-a,c-a))<=0;}
vector<P> convex_hull(vector<P> a){
	int n=(int)a.size(),t=0,i,w;
	sort(a.begin(),a.end());
	vector<P>q;
	for(i=0;i<n;i++){
		for(;t>1&&turn_left(q[t-2],a[i],q[t-1]);)t--,q.pop_back();
		q.push_back(a[i]);t++;
	}
	w=t;
	for(i=n-1;~i;i--){
		for(;t>w&&turn_left(q[t-2],a[i],q[t-1]);)t--,q.pop_back();
		q.push_back(a[i]);++t;
	}
	q.pop_back();
	return q;
}
