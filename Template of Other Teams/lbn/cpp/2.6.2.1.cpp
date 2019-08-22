struct P{int l,r,z;}p[N];
bool cmp(P a,P b){return ps[a.l]<ps[b.l]||ps[a.l]==ps[b.l]&&a.r<b.r;}
int main(){
	for(i=1;i<=n;i++)ps[i]=(i-1)/S;
	for(i=1;i<=m;i++)scanf("%d%d",&p[i].l,&p[i].r),p[i].z=i;
	sort(p+1,p+m+1,cmp);
	for(i=L=1,R=0;i<=m;i++){
		for(;R<p[i].r;)add(++R);
		for(;R>p[i].r;)del(R--);
		for(;L<p[i].l;)del(L++);
		for(;L>p[i].l;)add(--L);
		an[p[i].z]=sum;
	}
}
