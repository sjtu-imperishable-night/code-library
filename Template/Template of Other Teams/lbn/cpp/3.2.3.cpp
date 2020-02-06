string mini(string A){//最小表示法，返回最小表示 
	string AN;AN.clear();
	int i=0,j=1,k=0,x,n=A.length();
	for(;j<n&&k<n;){
		x=A[(i+k)%n]-A[(j+k)%n];
		x?x>0?i=max(j,i+k+1),j=i+1:j=j+k+1,k=0:k++;
	}
	for(j=0;j<n;j++)AN=AN+A[(i+j)%n];
	return AN;
}
