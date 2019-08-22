#include<bits/stdc++.h>//hdu2815
using namespace std;typedef long long LL;
LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
void exgcd(LL a,LL b,LL &x,LL &y){if(!b)x=1,y=0;else exgcd(b,a%b,y,x),y-=a/b*x;}
LL inv(LL a,LL n){LL x,y;exgcd(a,n,x,y);return(x+n)%n;}//用扩欧求出a在模n意义下的逆元
LL bsgs(LL a,LL b,LL n){//在(a,n)=1时求最小的x使得a^x mod n=b
    LL m,e=1,i;
    m=sqrt(n+0.5);//m=√n
    map<LL,LL>mp;mp[1]=0;//用map来做哈希，将a^0=1插入到哈希表中
    for(i=1;i<m;i++)
        if(!mp.count(e=e*a%n))//注意插入前要判断是否已经在哈希表中出现
            mp[e]=i;//将a^i插入到哈希表中
    e=e*a%n;e=inv(e,n);//e=a^m，求出其逆元后放到等式右边即可
    for(i=0;i<m;b=b*e%n,i++)if(mp.count(b))return i*m+mp[b];//从哈希表中判断是否有解
    return -1;//无解
}
LL exbsgs(LL a,LL b,LL n){//求最小的x使得a^x mod n=b
    LL V,k=0,d,e=1;
    for(;(d=gcd(a,n))!=1;){
        if(b%d)return b==1?0:-1;//如果(a,n)=1，那么要么x=0且b=1，要么无解
        k++;//记录除的次数k，累加到最后的答案中
        n=n/d;b=b/d;//b和模数n均除以(a,n)
        e=e*a/d%n;//记录a^k/(d_1*d_2*...*d_k)
        if(e==b)return k;//特判x=k时是否成立
    }
    V=bsgs(a,b*inv(e,n)%n,n);//将e移到右边，套用BSGS
    return ~V?V+k:V;//有解V返回V+k，否则无解
}
int main() {
    for(LL a,n,b,V;~scanf("%lld%lld%lld",&a,&n,&b);){
        V=exbsgs(a,b,n);
        if(b>=n||V==-1)puts("Orz,I can’t find D!");//无解
        else printf("%lld\n",V);
    }
}
