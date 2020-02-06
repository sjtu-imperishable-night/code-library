int dis(T k){return max(k.min[0]-I[0],0)+max(I[0]-k.max[0],0)+max(k.min[1]-I[1],0)+max(I[1]-k.max[1],0);} 
void query(int k,int o){//求离当前点最近点
	int d=abs(t[k].d[0]-I[0])+abs(t[k].d[1]-I[1]),dl=inf,dr=inf; 
	ans=min(ans,d);//更新答案
	if(t[k].l)dl=dis(t[t[k].l]); 
	if(t[k].r)dr=dis(t[t[k].r]); 
	if(dl<dr){//向子树找答案? 
		if(dl<ans)query(t[k].l,o^1); 
		if(dr<ans)query(t[k].r,o^1); 
	}else{ 
		if(dr<ans)query(t[k].r,o^1); 
		if(dl<ans)query(t[k].l,o^1); 
	} 
} 
