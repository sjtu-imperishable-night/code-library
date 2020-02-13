#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const double eps=1e-11;
int n;
double R;
struct dn{double x,y;}a[11];
dn operator+(dn u,dn v){
	return(dn){u.x+v.x,u.y+v.y};
}
dn operator-(dn u,dn v){
	return(dn){u.x-v.x,u.y-v.y};
}
dn operator*(double u,dn v){
	return(dn){u*v.x,u*v.y};
}
dn operator/(dn u,double v){
	return(dn){u.x/v,u.y/v};
}
double operator*(dn u,dn v){
	return u.x*v.x+u.y*v.y;
}
double operator/(dn u,dn v){
	return u.x*v.y-v.x*u.y;
}
double dis(dn o){
	return sqrt(max(0.,o.x*o.x+o.y*o.y));
}
double sec(dn u,dn v,double r){
	double c=(2*r*r-(u-v)*(u-v))/(2*r*r);
	return r*r*acos(c)/2;
}
double cc(dn u,dn v){
	//printf("uv%f %f %f %f\n",u.x,u.y,v.x,v.y);
	double da=dis(u),db=dis(v),dc=abs(u/v)/dis(u-v);
	if(da<eps||db<eps||dc<eps)return 0;
	if(da<R+eps&&db<R+eps)
		return abs(0.5*(u/v));
	dn ta=R*u/da,tb=R*v/db;
	//printf("tatb%f %f %f %f\n",ta.x,ta.y,tb.x,tb.y);
	if(dc>R-eps)return sec(ta,tb,R);
	dn o=-(u*(v-u))*(v-u)/((v-u)*(v-u))+u;
	double k=sqrt(max(0.,R*R-dc*dc));
	dn p=o-k*(v-u)/dis(v-u),q=2*o-p;
	//printf("pq!!!%f %f %f %f\n",o.x,o.y,q.x,q.y);
	if((p-u)*(v-u)>(v-u)*(v-u)-eps||(q-u)*(v-u)<eps)
		return sec(ta,tb,R);
	if(da>R-eps&&db>R-eps){
		return sec(ta,p,R)+abs(0.5*(p/q))+sec(tb,q,R);
	}
	if(da>R-eps)
		return abs(0.5*(p/v))+sec(ta,p,R);
	return abs(0.5*(u/q))+sec(tb,q,R);
	
}
double check(double x,double y){
	double ans=0;
	dn o=(dn){x,y};
	for(int i=1;i<=n;i++){
		ans+=((a[i]-o)/(a[i%n+1]-o)<0?-1:1)*cc(a[i]-o,a[i%n+1]-o);
	}
//	printf("%f %f:%f\n",x,y,ans);
	return ans;
}
double check(double x){
	double l=100,r=0;
	for(int i=1;i<=n;i++){
		dn u=a[i],v=a[i%n+1];
		if(abs(u.x-v.x)<eps)
			if(abs(u.x-x)<eps){
				l=min(l,min(u.y,v.y));
				r=max(r,max(u.y,v.y));
			}
			else continue;
		if(u.x>x+eps&&v.x>x+eps||u.x<x-eps&&v.x<x-eps)continue;
		double w=(x-u.x)/(v.x-u.x)*(v.y-u.y)+u.y;
		l=min(l,w);
		r=max(r,w);
	}
	l-=R;
	r+=R;
	for(int t=1;t<=50;t++){
		double m1=(l*2+r)/3,m2=(l+r*2)/3;
		if(check(x,m1)>check(x,m2))
			r=m2;
		else l=m1;
	}
	return check(x,l);
}
int main(){
	scanf("%d%lf",&n,&R);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i].x,&a[i].y);
	double l=100,r=0;
	for(int i=1;i<=n;i++)
		l=min(l,a[i].x),r=max(r,a[i].x);
	l-=R;
	r+=R;
	for(int t=1;t<=50;t++){
		double m1=(l*2+r)/3,m2=(l+r*2)/3;
		if(check(m1)>check(m2))
			r=m2;
		else l=m1;
//		printf("%f %f\n",l,r);
	}
	printf("%.20f\n",check(l));
}
