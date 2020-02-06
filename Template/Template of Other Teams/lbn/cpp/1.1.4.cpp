void ins(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;du[y]++;}
int main(){
	for(i=1;i<=n;i++)if(!du[i])q[++t]=i;
	for(;h^t;)for(i=fir[x=q[++h]];i;i=ne[i])if(!--du[la[i]])q[++t]=la[i];
}

