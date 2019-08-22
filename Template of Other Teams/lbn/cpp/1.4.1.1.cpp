bool fd(int x,int z){//x为左部一点，lk[]表示右部匹配的左部点
	for(int i=fir[x],y;i;i=ne[i])
		if(v[y=la[i]]!=z)
			if(v[y]=z,!lk[y]||fd(lk[y],z))return lk[y]=x,1;
	return 0;
}
