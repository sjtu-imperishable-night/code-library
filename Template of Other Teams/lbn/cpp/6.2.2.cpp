struct P{//一个点或者一个向量
	D x,y;
	P(D x=0,D y=0):x(x),y(y){}
	void in(){scanf("%lf%lf",&x,&y);}
	void out(){printf("%.7f %.7f\n",x,y);}
	D norm(){return sqrt(x*x+y*y);}//模长 
	D norm2(){return x*x+y*y;}
	P unit(){//单位向量
		D l=norm();
		return P(x/l,y/l);
	}
	P rot90(){return P(-y,x);}
	P _rot90(){return P(y,-x);}
	P rotate(D t){//弧度
		D c=cos(t),s=sin(t);
		return P(x*c-y*s,x*s+y*c);
	}
	D angle(){return atan2(y,x);}//角度 
};
bool operator==(P a,P b){return !cmp(a.x,b.x)&&!cmp(a.y,b.y);}
bool operator!=(P a,P b){return !(a==b);}
bool operator<(P a,P b){return cmp(a.x,b.x)==0?cmp(a.y,b.y)<0:cmp(a.x,b.x)<0;}
P operator-(P a){return P(-a.x,-a.y);}
P operator+(P a,P b){return P(a.x+b.x,a.y+b.y);}
P operator-(P a,P b){return P(a.x-b.x,a.y-b.y);}
P operator*(P a,D b){return P(a.x*b,a.y*b);}
P operator/(P a,D b){return P(a.x/b,a.y/b);}
D dj(P a,P b){return a.x*b.x+a.y*b.y;}//点积
D cj(P a,P b){return a.x*b.y-a.y*b.x;}//叉积
D dis(P a,P b){return (a-b).norm();}//距离
D area(P a,P b,P c){return cj(b-a,c-a)*.5; }//三角形面积
