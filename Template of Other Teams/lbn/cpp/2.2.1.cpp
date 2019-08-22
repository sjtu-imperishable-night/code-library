struct Heap{//小根堆
	int n,cnt,v[N],id[N],pos[N];
	Heap():n(0),cnt(0){}//构造一个空堆 
	Heap(int a[],int m):n(0),cnt(0){//将数组a[]中的元素按顺序插入所构造的堆，时间复杂度O(n) 
		for(int i=0;i<m;i++)v[++n]=a[i],id[n]=pos[n]=n;
		for(int i=n/2;i;i--)down(i);
	}
	void push(int z){//插入值z 
		v[++n]=z;
		pos[id[n]=++cnt]=n;
		up(n);
	}
	int top(){return v[1];}//堆顶元素的值 
	int pop(){//删除堆顶元素 
		swap(v[1],v[n]);
		swap(id[1],id[n--]);
		pos[id[1]]=1;
		down(1);
		return id[n+1];
	}
	int get(int i){return v[pos[i]];}//第i个插入堆中的元素值 
	void change(int i,int z){//将第i个元素修改为z 
		v[pos[i]]=z;
		down(pos[i]);
		up(pos[i]);
	}
	void erase(int i){//删除第i个元素 
		v[pos[i]]=-inf;
		up(pos[i]);
		pop();
	}
	void up(int i){
		int x=v[i],y=id[i];
		for(int j=i/2;j;j/=2){
			if(v[j]>x){
				pos[id[i]=id[j]]=i;
				v[i]=v[j];i=j;
			}else break;
		}
		v[i]=x;pos[id[i]=y]=i;
	}
	void down(int i){
		int x=v[i],y=id[i];
		for(int j=i*2;j<=n;j*=2){
			j+=j<n&&v[j]>v[j+1];
			if(v[j]<x){
				pos[id[i]=id[j]]=i;
				v[i]=v[j];i=j;
			}else break;
		}
		v[i]=x;pos[id[i]=y]=i;
	}
	bool empty(){return n==0;}
	int size(){return n;}
};
