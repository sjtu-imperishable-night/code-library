D cal(C o,D l,D r){
	return o.r*.5*(o.r*(r-l)+(o.c.x*(sin(r)-sin(l))-o.c.y*(cos(r)-cos(l))));
}
D circle_union_area(vector<C>p){//返回圆并面积 
	int n=p.size(),i,j,t;P p1,p2;
	pair<D,D>q[N];
	bool vs[N];D v1,v2,Rv,an=0;
	for(i=0;i<n;i++)vs[i]=0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)if(i!=j&&sgn(p[j].r-p[i].r)>=0&&!vs[j])
			if(circle_relationship(p[i],p[j])<=2)vs[i]=1;
	for(i=0;i<n;i++)if(!vs[i]){
		for(t=j=0;j<n;j++)if(!vs[j]&&i!=j&&circle_relationship(p[i],p[j])==3){
			circle_intersect(p[i],p[j],p1,p2);
			v1=(p1-p[i].c).angle(),v2=(p2-p[i].c).angle();
			if(sgn(v1)<0)v1+=pi*2;if(sgn(v2)<0)v2+=pi*2;
			if(sgn(v2-v1)>=0)q[++t]=make_pair(v1,v2);
			else q[++t]=make_pair(0,v2),q[++t]=make_pair(v1,pi*2);
		}
		sort(q+1,q+t+1);Rv=0;
		for(j=1;j<=t;j++){
			if(q[j].first>Rv)an+=cal(p[i],Rv,q[j].first);
			Rv=max(Rv,q[j].second);
		}
		an+=cal(p[i],Rv,pi*2);
	}
	return an;
}


D an[N];//an[k]返回被覆盖k次的面积
void circle_union_area(vector<C>p){
	int n=p.size(),V,i,j,k,t;P p1,p2;
	pair<D,int>q[N];
	bool vs[N];D v1,v2,Rv;
	for(i=0;i<n;i++)vs[i]=0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)if(i!=j&&sgn(p[j].r-p[i].r)>=0&&!vs[j])
			if(circle_relationship(p[i],p[j])==0)vs[i]=1;
	for(i=0;i<n;i++)if(!vs[i]){
		for(k=j=0;j<n;j++)if(sgn(p[j].r-p[i].r)>=0&&circle_relationship(p[i],p[j])<=2)k++;
		for(t=j=0;j<n;j++)if(!vs[j]&&i!=j&&circle_relationship(p[i],p[j])==3){
			circle_intersect(p[i],p[j],p1,p2);
			v1=(p1-p[i].c).angle(),v2=(p2-p[i].c).angle();
			if(sgn(v1)<0)v1+=pi*2;if(sgn(v2)<0)v2+=pi*2;
			if(sgn(v2-v1)>=0)q[++t]=make_pair(v1,1),q[++t]=make_pair(v2,-1);
			else q[++t]=make_pair(0,1),q[++t]=make_pair(v2,-1),q[++t]=make_pair(v1,1),q[++t]=make_pair(pi*2,-1);
		}
		sort(q+1,q+t+1);Rv=0;
		for(j=1;j<=t;j++){
			an[V+k]+=cal(p[i],q[j-1].first,q[j].first);
			V+=q[j].second;Rv=q[j].first;
		}
		an[V+k]+=cal(p[i],Rv,pi*2);
	}
	for(i=1;i<n;i++)an[i]-=an[i+1];
}
