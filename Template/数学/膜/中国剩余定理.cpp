// 51nod 1079
#include<iostream>
using namespace std;
int gcd(int x,int y)
{
	if(x==0)
		return y;
	if(y==0)
		return x;
	return gcd(y,x%y);
}
long long exgcd(long long a,long long b,long long &x,long long &y)  
{  
    if(b==0)  
    {  
        x=1;
        y=0;  
        return a;  
    }  
    long long ans=exgcd(b,a%b,x,y);
    long long temp=x;
    x=y;
    y=temp-a/b*y;
    return ans;
}
void fix(long long &x,long long &y)
{
	x%=y;
	if(x<0)
		x+=y;
}
bool solve(int n, std::pair<long long, long long> input[],std::pair<long long, long long> &output)
{
	output = std::make_pair(1, 1);
	for(int i = 0; i < n; ++i)
	{
		long long number, useless;
		exgcd(output.second, input[i].second, number, useless);
		long long divisor = gcd(output.second, input[i].second);
		if((input[i].first - output.first) % divisor)
		{
			return false;
		}
		number *= (input[i].first - output.first) / divisor;
		fix(number,input[i].second);
		output.first += output.second * number;
		output.second *= input[i].second / divisor;
		fix(output.first, output.second);
	}
	return true;
}
pair<long long,long long> input[101010],output;
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>input[i].second>>input[i].first;
	solve(n,input,output);
	cout<<output.first<<endl;
	return 0;
}
