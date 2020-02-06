#include<bits/stdc++.h>//一个元素有多个映射
#define pii pair<int,int>
using namespace std;
multimap<int,int>mp;
multimap<int,int>::iterator it;
pair<multimap<int,int>::iterator, multimap<int,int>::iterator> ret;
int main(){
	mp.insert(pii(5,6));mp.insert(pii(5,7));
	mp.insert(pii(5,4));mp.insert(pii(6,8));
	ret=mp.equal_range(5);//用equal_range()函数找到元素5的所有映射
	for(it=ret.first;it!=ret.second;it++)
		printf("%d ",(*it).second);//6 7 4	
}
