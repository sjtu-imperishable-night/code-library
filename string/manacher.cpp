#include<iostream>
#include<cstring>
using namespace std;
char Mana[202020];
int cher[202020];
int Manacher(char *S)
{
	int len=strlen(S),id=0,mx=0,ret=0;
	Mana[0]='$';
	Mana[1]='#';
	for(int i=0;i<len;i++)
	{
		Mana[2*i+2]=S[i];
		Mana[2*i+3]='#';
	}
	Mana[2*len+2]=0;
	for(int i=1;i<=2*len+1;i++)
	{
		if(i<mx)
			cher[i]=min(cher[2*id-i],mx-i);
		else
			cher[i]=0;
		while(Mana[i+cher[i]+1]==Mana[i-cher[i]-1])
			cher[i]++;
		if(cher[i]+i>mx)
		{
			mx=cher[i]+i;
		 	id=i;
		}
		ret=max(ret,cher[i]);
	}
	return ret;
}
char S[101010];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin>>S;
	cout<<Manacher(S)<<endl;
	return 0;
}
