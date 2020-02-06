vector<P> minkowski(vector<P> a,vector<P> b){//给定两个点集a和b，求它们闵可夫斯基和的凸包
	a=convex_hull(a);b=convex_hull(b);//先求一遍各自的凸包
	vector<P> c;c.push_back(a[0]+b[0]);//将左下角的点加入
	int n=a.size(),m=b.size(),i,j;P x,y;
	a.push_back(a[0]);b.push_back(b[0]);
	for(i=0,j=0;i<n||j<m;){//按顺序判断加入
		x=a[i]+b[j+1];y=a[i+1]+b[j];
		if(sgn(cj(x-c.back(),y-c.back()))>=0)c.push_back(x),j++;
		else c.push_back(y),i++;
	}
	c.pop_back();
	return c;
}
