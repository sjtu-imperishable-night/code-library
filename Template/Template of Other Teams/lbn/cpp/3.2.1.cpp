void kmp(string A,int*p){//A为模式串，p为失配数组 
	int n=A.length(),i=1,j=0;
	for(CL(p);i<n;i++){
		for(;j&&A[j]^A[i];j=p[j-1]);
		if(A[i]==A[j])j++;
		p[i]=j;
	}
}
int gans(string A,string B,int*p){//B为标准串，A为待匹配串，p为失配数组 
	int n=B.length(),m=A.length(),i=1,j=0;
	for(i=0;i<m;i++){
		for(;j&&B[j]^A[i];j=p[j-1]);
		if(B[j]==A[i])j++;
		if(j==n)an++,j=p[j-1];
	}
	return an;
}
