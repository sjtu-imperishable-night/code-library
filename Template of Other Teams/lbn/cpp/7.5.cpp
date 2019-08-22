#include<bits/stdc++.h>//UOJ179，模板题
#define eps 1e-8
#define inf 1e100
#define N 111
double v,p,a[N][N],b[N],c[N],an[N*2];
int n,m,i,j,e,l,q[N*2];
void pivot(int l,int e){
	int i,j;
	a[l][e]=1/a[l][e];//将非基本变量所在列的值a_le 修改为它的倒数
	b[l]*=a[l][e];
	for(i=1;i<=n;i++)if(i!=e)a[l][i]*=a[l][e]; //将该行其它元素均乘以修改后的a_le
	for(i=1;i<=m;i++)//将式子剩余部分变形
		if(i!=l&&fabs(a[i][e])>eps){//注意精度
		b[i]-=a[i][e]*b[l];
		for(j=1;j<=n;j++)
		if(j!=e)//对于不是非基本变量所在列的元素a_ij，其值减去a_ie*a_lj
			a[i][j]-=a[i][e]*a[l][j];
		a[i][e]*=-a[l][e];//对于非基本变量所在列的元素a_ie，其值乘以修改后的a_le的相反数
	}
	v+=c[e]*b[l];//目前的目标函数值要更改
	for(i=1;i<=n;i++)//注意对应系数的行也是其它行，一样地修改
		if(i!=e)c[i]-=c[e]*a[l][i]; 
	c[e]*=-a[l][e];
	std::swap(q[e],q[l+n]);//记录方案
}
void pre(){
	for(;;){
		for(i=m;i;i--)//找到对应b_e<0的非基本变量x_e（这里为i）
		if(b[i]<-eps)break; 
		if(!i)break;
		for(j=n;j;j--)//找到对应a_el<0的基本变量x_(n+l)（这里为n+j）
		if(a[i][j]<-eps)break;
		if(!j)return puts("Infeasible"),0;//无解
		pivot(i,j);//通过转轴操作调整
	}
}
int main(){
	scanf("%d%d",&n,&m); 
	for(i=1;i<=n;i++)scanf("%lf",&c[i]),q[i]=i;//读入约束和目标函数
	for(i=1;i<=m;scanf("%lf",&b[i]),i++)
	for(j=1;j<=n;j++)scanf("%lf",&a[i][j]);
	pre();//特殊处理存在b_i<0的情况
	for(;;){//寻找更优解
		for(i=n;i;i--)if(c[i]>eps)break; //选择系数大于0的
		if(!i)break;//如没有非基本变量对应的系数为正，则找到最优解
		for(p=inf,e=i,i=1;i<=m;i++)
			if(a[i][e]>eps&&p>b[i]/a[i][e])
				p=b[i]/a[i][e],l=i;//找到满足a_le>0且b_l/a_le最小的基本变量
		if(p==inf)return puts("Unbounded"),0; //如找不到可行的基本变量，则最优解无穷大
		pivot(l,e);//转轴操作，交换非基本变量x_e和基本变量x_(n+l)
	}
	printf("%.8lf\n",v);//输出答案
	for(i=n+1;i<=n+m;i++)an[q[i]]=b[i-n];
	for(i=1;i<=n;i++)printf("%.8lf ",an[i]);//输出方案
}
