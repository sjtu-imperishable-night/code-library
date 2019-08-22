void exgcd(LL a,LL b,LL &x,LL &y){
if(!b){x=1;y=0;return;}exgcd(b,a%b,y,x);y-=x*(a/b);}
LL Pw(LL a,LL b,LL p){
LL V=1;for(a%=p;b;a=a*a%p,b>>=1)if(b&1)V=V*a%p;return V;}
LL inv(LL a,LL p){LL x,y;exgcd(a,p,x,y);return(x+p)%p;}
U fac(int k,LL n){//求n! mod pk^tk，返回值为U{不包含质因子pk的值，质因子pk出现的次数}
    if (!n)return U{1,0};//n=0，返回{1,0}
    LL x=n/p[k],y=n/P[k],ans=1;int i;
    if(y){//求出循环节的答案
        for(i=2;i<P[k];i++)if(i%p[k])ans=ans*i%P[k];//求出一个循环节答案
        ans=Pw(ans,y,P[k]);//快速幂求出所有循环部分的答案
    }
    for(i=y*P[k];i<=n;i++)if(i%p[k])ans=ans*i%M;//求出零散部分的答案
    U z=fac(k,x);//对于pk的倍数，递归求解
    return U{ans*z.x%M,x+z.z};//分解出了n/pk个pk，并统计递归的贡献
}
LL get(int k,LL n,LL m){//求C(n,m) mod pk^tk
    U a=fac(k,n),b=fac(k,m),c=fac(k,n-m);//分成三部分，分别求解
    return Pw(p[k],a.z-b.z-c.z,P[k])*a.x%P[k]*inv(b.x,P[k])%P[k]*inv(c.x,P[k])%P[k];
}//将含有质因子pk的分开求解，保证正确性
LL CRT(){//中国剩余定理
    LL d,w,y,x,ans=0;
for(int i=1;i<=l;i++)
w=M/P[i],exgcd(w,P[i],x,y),ans=(ans+w*x*a[i])%M;
    return(ans+M)%M;
}
LL C(LL n,LL m){
    for(int i=1;i<=l;i++)a[i]=get(i,n,m);//求出每个模pi^ai的答案
    return CRT();//将模每个pi^ai的答案合并
}
    scanf("%d%lld%lld",&M,&n,&m);jj=M;//M为模数
    for(i=2;i*i<=jj;i++)if(jj%i==0)//将M暴力分解质因数
        for(p[++l]=i,P[l]=1;jj%i==0;P[l]*=p[l])
            jj/=i;//p[]记录所有质数p，P[]记录p^t
    if(jj>1)l++,p[l]=P[l]=jj;
    printf("%lld\n",C(n,m));
