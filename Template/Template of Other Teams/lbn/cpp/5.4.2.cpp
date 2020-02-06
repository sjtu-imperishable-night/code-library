#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int t,i,q[66];LL n;
LL mul(LL a,LL b,LL p){//快速乘
    LL v=0;
    for(;b;a=(a+a)%p,b>>=1)
        if(b&1)v=(v+a)%p;
    return v;
}
LL pw(LL a,LL b,LL p){//快速幂
    LL v=1;
    for(a%=p;b;a=mul(a,a,p),b>>=1)
        if(b&1)v=mul(v,a,p);
    return v;
}
LL gcd(LL a,LL b){//gcd，注意负数
    if(a<0)return gcd(-a,b);  
    return b?gcd(b,a%b):a;  
}
bool ck(LL a,LL n,LL d,LL t){
    LL V=pw(a,d,n),la=V,i;//从a^d  mod n开始做
    for(i=1;i<=t;la=V,i++){
        V=mul(V,V,n);//不断对a^d平方
        if(V==1&&la!=1&&la!=n-1)return 1;//平方后的值是1，平方前的值如不是1或n-1，则不是质数
    }
    return V!=1;//a^(d*2^r )mod n≠1，则不是质数
}
bool miller_rabin(LL n){//米勒罗宾，判断n是否为质数
    if(n==2)return 1;if(n<2||n%2==0)return 0;
    LL x=n-1,t=0,i;for(;x%2==0;x>>=1)t++;//取出2的次幂
    for(i=20;i;i--)//尝试20次
        if(ck(rand()%(n-1)+1,n,x,t))return 0;//没有通过素数测试，不是素数
    return 1;
}
LL pollard_rho(LL n,LL c){
    LL i=1,k=2,x0=rand()%(n-1)+1,y=x0,d;//随机x_0∈[1,n)
    for(;;){
        i++;
        x0=(mul(x0,x0,n)+c)%n;//x_(i+1)=x_i^2+c
        d=gcd(y-x0,n);//计算d=gcd?(a-b,n)
        if(d!=1&&d!=n)return d;//如果d≠1且d≠n，则d是n的因子
        if(y==x0)return n;//出现循环，退出
        if(i==k)y=x0,k+=k;//i是2的次幂，令y=x_i
    }
}
void find_factor(LL n){//将n分解质因数
    if(miller_rabin(n)){q[++t]=n;return;}//n为素数
    LL p=n;
    for(;p>=n;)//尝试分解
        p=pollard_rho(n,rand()%(n-1)+1);//随机c∈[1,n)
    find_factor(p);//递归求解
    find_factor(n/p);
}
int main(){
    scanf("%lld",&n);
    find_factor(n);
    sort(q+1,q+t+1);
    for(i=1;i<=t;i++)printf("%lld ",q[i]);
}
