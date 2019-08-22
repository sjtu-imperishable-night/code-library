struct P{
	int x,y;
	bool operator<(P a)const{return a.x<x||a.x==x&&a.y<y;}
};
set<P>S;
