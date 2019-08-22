#include<bits/stdc++.h>//SGU261，模板题 
typedef long long LL; 
using namespace std;
LL p,n,a,q[99],AN[100100];int t,i,e;
LL Pw(LL a,LL b,LL p){LL v=1;for(;b;a=a*a%p,b>>=1)if(b&1)v=v*a%p;return v;}
LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
LL exgcd(LL a,LL b,LL&x,LL&y){
    if(!b){x=1;y=0;return a;}
    LL t=exgcd(b,a%b,y,x);
    y-=a/b*x;return t;
}
LL inv(LL a,LL n){LL x,y;exgcd(a,n,x,y);return(x+n)%n;}
LL bsgs(LL a,LL b,LL n){
    LL m=sqrt(n+0.5),e=1,i;map<LL,LL>mp;mp[1]=0;
    for(i=1;i<m;i++)if(!mp.count(e=e*a%n))mp[e]=i;
    for(e=inv(e*a%n,n),i=0;i<m;b=b*e%n,i++)if(mp.count(b))return i*m+mp[b];
    return -1;
}
bool ok(LL g,LL p){//验证g是否是模p的原根
    for(int i=1;i<=t;i++)//如果g^((p-1)/qi) mod p=1，那么g不是模p的原根
        if(Pw(g,(p-1)/q[i],p)==1)return 0;
    return 1;
}
LL primitive_root(LL p){//求原根
    LL i,n=p-1,g=1;t=0;
    for(i=2;i*i<=n;i++)//分解质因数
        if(n%i==0)for(q[++t]=i;n%i==0;n/=i);
    if(n!=1)q[++t]=n;
    for(;;g++)//暴力枚举判断
        if(ok(g,p))return g;
}
void n_residue(LL a,LL n,LL p){//求x^n mod p=a的所有解
    LL i,g,m,x,y,d,M=p-1,w;
    g=primitive_root(p);//求出p的原根
    m=bsgs(g,a,p);//求出以g为底a对p取模的指标
    if(a==0){AN[++e]=0;return;}//特判a=0,解为x=0
    if(m==-1)return;//求指标时无解
    d=exgcd(n,M,x,y);//求出n在模p-1意义下的逆元
    if(m%d)return;//扩展欧几里得找不到解
    x=((x%M+M)%M)*(m/d)%M;//求出初始解
    for(i=1;i<=d;i++)//依次求出所有的解
        AN[++e]=Pw(g,(x+M/d*i)%M,p);//求出的解是指标，取幂后变为实际的x
    sort(AN+1,AN+e+1);//对答案排序
    e=unique(AN+1,AN+e+1)-AN-1;//去重
}
int main(){
    scanf("%lld%lld%lld",&p,&n,&a);
    n_residue(a,n,p);
    printf("%d\n",e);
    for(i=1;i<=e;i++)printf("%lld\n",AN[i]);
}
