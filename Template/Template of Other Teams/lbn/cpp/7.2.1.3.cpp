void fz(int l,int r){
	if(l==r)return;int md=l+r>>1;
	fz(l,md);fz(md+1,r);
	int i=l,j=md+1,k=l;
	for(;k<=r;)b[k++]=(i<=md&&(a[i]<a[j]||j>r))?a[i++]:a[j++];
	for(i=l;i<=r;i++)a[i]=b[i];
}
