void rd(int &x){//外部调用rd(x)即可
	char ch;
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for(x=0;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
}
