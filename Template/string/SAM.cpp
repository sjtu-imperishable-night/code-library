#include<iostream>
#include<cstring>
using namespace std; 
const int MaxPoint=1010101;
struct Suffix_AutoMachine{
	int son[MaxPoint][27],pre[MaxPoint],step[MaxPoint],right[MaxPoint],last,root,num;
	int NewNode(int stp)
	{
		num++;
		memset(son[num],0,sizeof(son[num]));
		pre[num]=0;
		step[num]=stp;
		return num;
	}
	Suffix_AutoMachine()
	{
		num=0;
		root=last=NewNode(0);
	}
	void push_back(int ch)
	{
		int np=NewNode(step[last]+1);
		right[np]=1; 
		step[np]=step[last]+1;
		int p=last;
		while(p&&!son[p][ch])
		{
			son[p][ch]=np;
			p=pre[p];
		}
		if(!p)
			pre[np]=root;
		else
		{
			int q=son[p][ch];
			if(step[q]==step[p]+1)
				pre[np]=q;
			else
			{
				int nq=NewNode(step[p]+1);
				memcpy(son[nq],son[q],sizeof(son[q]));
				step[nq]=step[p]+1;
				pre[nq]=pre[q];
				pre[q]=pre[np]=nq;
				while(p&&son[p][ch]==q)
				{
					son[p][ch]=nq;
					p=pre[p];
				}
			}
		}
		last=np;
	}
};
/*

int arr[1010101];
bool Step_Cmp(int x,int y)
{
	return S.step[x]<S.step[y];
}
void Get_Right()
{
	for(int i=1;i<=S.num;i++)
		arr[i]=i;
	sort(arr+1,arr+S.num+1,Step_Cmp);
	for(int i=S.num;i>=2;i--)
		S.right[S.pre[arr[i]]]+=S.right[arr[i]];
}
*/ 
int main()
{
	
	return 0;
}
