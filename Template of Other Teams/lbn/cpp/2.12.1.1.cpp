struct Cmp{//重载运算符，这里将大的数放在前面
	bool operator()(int a,int b){return a>b;}
};
set<int,Cmp>S;
