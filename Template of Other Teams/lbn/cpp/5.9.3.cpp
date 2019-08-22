LL C(int n,int m){//O(1)求C(n,m)
    return n<m?0:1ll*pw[n]*I[n-m]%M*I[m]%M;
}
LL lucas(LL n,LL m,LL p){//卢卡斯定理求组合数
    return !m?1:lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;
}
for(I[1]=1,i=2;i<=N;i++)I[i]=1ll*(M-M/i)*I[M%i]%M;//O(n)递推逆元
for(pw[0]=inv[0]=i=1;i<=N;i++)//推出阶乘及阶乘的逆
    I[i]=1ll*I[i]*I[i-1]%M,pw[i]=1ll*pw[i-1]*i%M;
