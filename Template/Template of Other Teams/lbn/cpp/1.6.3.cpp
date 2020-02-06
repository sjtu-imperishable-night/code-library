void tarjan(int x){//伪代码
	F[x]=x;c[x]=1;
	for(int i=fir[x];i;i=ne[i])if(!c[y=la[i]])tarjan(y),F[y]=x;
	for(int i=fir[x];i;i=ne[i])if(c[la[i]]==2)answer<x,y>=fd(y);
	c[x]=2;
}
