P line_intersect(L a,L b){//直线相交
	D s1=cj(a.t-a.s,b.s-a.s),s2=cj(a.t-a.s,b.t-a.s);
	return (b.s*s2-b.t*s1)/(s2-s1);
}
bool turn_left(P a,P b,P c){return sgn(cj(b-a,c-a))>=0;}
bool turn_right(P a,P b,P c){return sgn(cj(b-a,c-a))<=0;}
bool turn_left(L l,P p){return turn_left(l.s,l.t,p);}
vector<P> half_plane_intersect(vector<L>p){//半平面交，返回向量左手边的区域
	int n=(int)p.size(),i;
	typedef pair<D,L>polar;
	vector<polar>g;
	g.resize(n);
	for(int i=0;i<n;i++){
		P v=p[i].t-p[i].s;
		g[i]=make_pair(atan2(v.y,v.x),p[i]);
	}
	sort(g.begin(),g.end(),[](polar a,polar b){
		if(cmp(a.first,b.first)==0)return sgn(cj(a.second.t-a.second.s,b.second.t-a.second.s))<0;		
		else return cmp(a.first,b.first)<0;
	});
	p.resize(unique(g.begin(),g.end(),[](polar a,polar b){return cmp(a.first,b.first)==0;})-g.begin());
	for(int i=0;i<n;i++)p[i]=g[i].second;
	int h=0,t=-1;
	vector<L>q;
	for(int i=0;i<n;i++){
		for(;h<t&&!turn_left(p[i],line_intersect(q[t-1],q[t]));)t--,q.pop_back();
		for(;h<t&&!turn_left(p[i],line_intersect(q[h],q[h+1]));)h++;
		t++;q.push_back(p[i]);
	}
	for(;t-h>1&&!turn_left(q[h],line_intersect(q[t-1],q[t]));t--)q.pop_back();
	for(;t-h>1&&!turn_left(q[t],line_intersect(q[h],q[h+1]));)h++;
	if(t-h<2)return vector<P>();
	vector<P>ans;
	ans.resize(q.size());
	for(i=0;i<(int)q.size();i++)
		ans[i]=line_intersect(q[i],q[(i+1)%q.size()]);
	return ans;
}
