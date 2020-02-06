void exkmp(string A,string B,int*ex){//B为标准串，A为待匹配串，ex为extend数组 
	int i,j=0,o=0,x,L,la=A.length(),lb=B.length();
	for(kmp(B,p);j<la&&j<lb&&A[j]==B[j];j++);
	for(ex[0]=j,i=1;i<la;i++){
		x=o+ex[o];L=p[i-o];
		if(i+L<x)ex[i]=L;else{
			for(L=max(x-i,0);i+L<la&&L<lb&&A[i+L]==B[L];)L++;
			ex[i]=L;o=i;
		}
	}
}
