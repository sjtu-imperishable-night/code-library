struct P3{
	D x,y,z;
	P3(D x=0,D y=0,D z=0):x(x),y(y),z(z){}
	void in(){scanf("%lf%lf%lf",&x,&y,&z);}
	void out(){printf("%.7f %.7f %.7f\n",x,y,z);}
	D norm(){return sqrt(x*x+y*y+z*z);}
	D norm2(){return x*x+y*y+z*z;}
	P3 unit(){
		D l=norm();
		return P3(x/l,y/l,z/l);
	}
	P3 rotate(D w){//三维绕轴旋转，不保证正确 
	//大拇指指向x轴正方向时，4指弯曲由y轴正方向指向z轴正方向，大拇指沿着源点到点(x,y,z)的向量，4指弯曲方向旋转w弧度
	//(x,y,z)*A=(x_new,y_new,z_new) 行向量向右乘转移矩阵 
		D s=norm2(),a[3][3];
		a[0][0]=((y*y+z*z)*cos(w)+x*x)/s;
		a[0][1]=x*y*(1-cos(w))/s+z*sin(w)/sqrt(s);
		a[0][2]=x*z*(1-cos(w))/s-y*sin(w)/sqrt(s);
		a[1][0]=x*y*(1-cos(w))/s-z*sin(w)/sqrt(s);
		a[1][1]=((x*x+z*z)*cos(w)+y*y)/s;
		a[1][2]=y*z*(1-cos(w))/s+x*sin(w)/sqrt(s);
		a[2][0]=x*z*(1-cos(w))/s+y*sin(w)/sqrt(s);
		a[2][1]=y*z*(1-cos(w))/s+x*sin(w)/sqrt(s);
		a[2][2]=((x*x+y*y)*cos(w)+z*z)/s;
		return P3(x*a[0][0]+y*a[1][0]+z*a[2][0],x*a[0][1]+y*a[1][1]+z*a[2][1],x*a[0][2]+y*a[1][2]+z*a[2][2]);
	}
};
bool operator==(P3 a,P3 b){return !cmp(a.x,b.x)&&!cmp(a.y,b.y);}
bool operator!=(P3 a,P3 b){return !(a==b);}
bool operator<(P3 a,P3 b){
	if(cmp(a.x,b.x))return cmp(a.x,b.x)<0;
	if(cmp(a.y,b.y))return cmp(a.y,b.y)<0;
	return cmp(a.z,b.z)<0;
}
P3 operator-(P3 a){return P3(-a.x,-a.y,-a.z);}
P3 operator+(P3 a,P3 b){return P3(a.x+b.x,a.y+b.y,a.z+b.z);}
P3 operator-(P3 a,P3 b){return P3(a.x-b.x,a.y-b.y,a.z-b.z);}
P3 operator*(P3 a,D b){return P3(a.x*b,a.y*b,a.z*b);}
P3 operator/(P3 a,D b){return P3(a.x/b,a.y/b,a.z/b);}
P3 cj(P3 a,P3 b){return P3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);}//叉积 
D dj(P3 a,P3 b){return a.x*b.x+a.y*b.y+a.z*b.z;}//点积 
D hhj(P3 a,P3 b,P3 c){return dj(a,cj(b,c));}//混合积，混合积/6即为三个向量构成四面体的体积 
D dis(P3 a,P3 b){return (a-b).norm();}//距离 
D area(P3 a,P3 b,P3 c){return cj(b-a,c-a).norm()*.5;}//空间三角形面积 
