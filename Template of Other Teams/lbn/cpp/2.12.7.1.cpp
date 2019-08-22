#include<bits/stdc++.h>
#include<ext/rope>
#define N 50505
using namespace std;using namespace __gnu_cxx;
char s[N];crope R,his[N];string ss;int n,lx,p,x,v,num,cur;
int main(){
	for(scanf("%d",&n);n--;){
		scanf("%d",&lx);
		if(lx==1){//在p位置后面插一个字符串s
			scanf("%d%s",&p,s);
			R.insert(p,s);
			his[++cur]=R;
		}
		if(lx==2){//从第p个字符开始删掉x个字符
			scanf("%d%d",&p,&x);
			R.erase(p-1,x);
			his[++cur]=R;
		}
		if(lx==3){//在第v个版本中从第p个位置开始取x个字符并输出
			scanf("%d%d%d",&v,&p,&x);
			ss=his[v].substr(p-1,x).c_str();
			num+=count(ss.begin(),ss.end(),'c');
			printf("%s\n",ss.c_str());
		}
	}
}
