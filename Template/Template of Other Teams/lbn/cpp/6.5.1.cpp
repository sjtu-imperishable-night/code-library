bool in_polygon(P p,vector<P>E){
	int n=(int)E.size(),cnt=0,i;
	for(i=0;i<n;i++){
		P a=E[i],b=E[(i+1)%n];
		if(point_on_segment(p,L(a,b)))return 1;
		int x=sgn(cj(p-a,b-a)),y=sgn(a.y-p.y),z=sgn(b.y-p.y);
		if(x>0&&y<=0&&z>0)cnt++;
		if(x<0&&z<=0&&y>0)cnt--;
	}
	return cnt!=0;
}
