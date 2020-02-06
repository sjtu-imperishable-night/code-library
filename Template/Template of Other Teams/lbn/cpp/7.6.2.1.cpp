void pr(int k){
	static int s[12];int t;bool f=0;
	if(k<0)f=1,k=-k;
	for(t=0;k>0;k/=10)s[++t]=k%10;
	if(f)putchar('-');
	if(!t)putchar(48); 
	for(;t;)putchar(s[t--]+48);puts("");
}