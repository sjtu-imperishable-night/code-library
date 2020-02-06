void bd(int m1,int n1,int m2,int n2){//依靠m1/n1,(m1+m2)/(n1+n2),m2/n2的法则递归构造
	if(m1+m2>n||n1+n2>n)return;
	bd(m1,n1,m1+m2,n1+n2);
	q[++t].a=m1+m2;
	q[++t].b=n1+n2;
	bd(m1+m2,n1+n2,m2,n2);
}
