for(i=(1<<k)-1;i<1<<n;i=(((i&~y)/x)>>1)|y){//要保证k>0
	//i is a subset
	x=i&-i;y=x+i;
}
