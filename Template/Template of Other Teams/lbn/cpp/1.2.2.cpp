struct P{int x,y,z;}p[M];//边(x,y)的边权为z
bool cmp(P a,P b){return a.z<b.z;}
int fd(int x){return F[x]==x?x:F[x]=fd(F[x]);}//并查集
void Kruskal(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
	for(i=1;i<=n;i++)F[i]=i;
	sort(p+1,p+m+1,cmp);
	for(i=1;i<=m;i++){
		x=fd(p[i].x);y=fd(p[i].y);
		if(x!=y)F[x]=y,an+=p[i].z;
	}
}
