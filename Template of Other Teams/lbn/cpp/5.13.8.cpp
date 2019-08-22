void FWT(int w){//w=1为tf，w=0为utf
	int i,j,k,x,y;//这里的运算符为xor
	for(i=1;i<N;i*=2)
		for(j=0;j<N;j+=i*2){
			x=a[j+k],y=a[i+j+k];
 			for(k=0;k<i;k++)if(w){
			a[j+k]=(x+y)%M;
			a[i+j+k]=(x-y+M)%M;
			//xor a[j+k]=x+y a[i+j+k]=x-y
			//and a[j+k]=x+y
			//or  a[i+j+k]=x+y
		}else{
			a[j+k]=500000004ll*(x+y)%M;//500000004相当于逆元，即/2
			a[i+j+k]=500000004ll*(x-y+M)%M;
			//xor a[j+k]=(x+y)/2 a[i+j+k]=(x-y)/2
			//and a[j+k]=x-y
			//or  a[i+j+k]=y-x
		}
	}
}
