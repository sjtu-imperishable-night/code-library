vector<P>cut(vector<P>c,L p){
	vector<P>q;int n=c.size(),i,j,k;
	if(c.empty())return q;
	for(i=0;i<n;i++){
		j=(i+1)%n;
		if(!turn_right(p.s,p.t,c[i]))q.push_back(c[i]);
		if(two_side(c[i],c[j],p))
			q.push_back(line_intersect(p,L(c[i],c[j])));
	}
	return q;
}
