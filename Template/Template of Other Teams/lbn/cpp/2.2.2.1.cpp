int merge(int x,int y){
	if(!x||!y)return x+y;//只剩某一子数（点）的情况 
	if(val[x]<val[y])swap(x,y);//以x为最大点
	c[x][1]=merge(c[x][1],y);
	F[c[x][1]]=x; 
	if(d[c[x][1]]>d[c[x][0]])swap(c[x][0],c[x][1]);//维护左偏树性质
	if(!c[x][1])d[x]=0;else d[x]=d[c[x][1]]+1;//左偏树性质
	return x;
}
