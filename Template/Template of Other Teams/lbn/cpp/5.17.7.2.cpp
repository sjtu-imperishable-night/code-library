int cmp(__int128 a1,__int128 b1,__int128 a2,__int128 b2){
	if(a1*b2==b1*a2)return 0;
	return a1*b2>b1*a2?1:-1;
}
bool ok(int a1,int b1){
	if(cmp(a1,b1,anlfz,anlfm)>=0&&cmp(a1,b1,anrfz,anrfm)<0)
		return printf("%d %d\n",a1,b1),1;
	return 0;
}
void fd(int a1,int b1,int a2,int b2){
	int a3=a1+a2,b3=b1+b2;
	if(ok(a1,b1))return;if(ok(a2,b2))return;if(ok(a3,b3))return;
	if(cmp(a3,b3,anrfz,anrfm)>=0){//往左
		int l=1,r=(1000000000-b2)/b1,md,an;
		for(;l<=r;){
			md=l+r>>1;
			if(cmp(a1*md+a2,b1*md+b2,anrfz,anrfm)>=0)an=md,l=md+1;else r=md-1;
		}
		fd(a1,b1,a1*an+a2,b1*an+b2);
	}else{//往右
		int l=1,r=(1000000000-b1)/b2,md,an;
		for(;l<=r;){
			md=l+r>>1;
			if(cmp(a1+a2*md,b1+b2*md,anlfz,anlfm)<0)an=md,l=md+1;else r=md-1;
		}
		fd(a1+a2*an,b1+b2*an,a2,b2);
	}
}
