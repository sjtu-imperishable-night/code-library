void ins(int x,int y){//x->y
	if(!fir[x])L[x]=y;else R[fir[x]]=y;
	fir[x]=y;
}