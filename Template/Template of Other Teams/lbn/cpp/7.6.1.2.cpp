void rd(int &x){
	bool f=0;char ch;
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=1;
	for(x=0;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';if(f)x=-x;
}