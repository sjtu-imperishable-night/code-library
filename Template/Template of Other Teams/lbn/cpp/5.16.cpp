int f[N],sg[N],hash[N];//f[]可以取走的石子个数
void getSG(int n){//sg[]:0~n的SG函数值
	int i,j;//hash[]:mex{}
	memset(sg,0,sizeof(sg));memset(v,0,sizeof(v));
	for(i=1;i<=n;i++){
		for(j=1;f[j]<=i;j++)v[sg[i-f[j]]]=i;
		for(j=0;j<=n;j++)//求mes{}中未出现的最小的非负整数
			if(v[j]!=i){sg[i]=j;break;}
	}
}
