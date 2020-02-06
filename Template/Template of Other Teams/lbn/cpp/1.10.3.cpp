int getlca(int x,int y){
	for(;bl[x]!=bl[y];x=F[bl[x]])if(h[bl[x]]<h[bl[y]])swap(x,y);
	return pos[x]>pos[y]?y:x;
}
