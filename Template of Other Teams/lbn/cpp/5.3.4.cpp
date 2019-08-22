LL P(LL n){//求欧拉函数前缀和
    if(n<M)return phi[n];//设M为n^(2/3)，这里的phi[n]为欧拉函数的前缀和
    LL x=1ll*n*(n+1)/2,i=2,la;//初值为n*(n+1)/2，注意i从2开始
    for(;i<=n;i=la+1)//把n/i相等的归为一类，一起计算
        la=n/(n/i),x-=P(n/i)*(la-i+1);//根据推导的公式计算
    return x;
}
LL U(LL n){//求莫比乌斯函数前缀和
    if(n<M)return u[n];
    LL x=1,i=2,la;//初值为1
    for(;i<=n;i=la+1)
        la=n/(n/i),x-=U(n/i)*(la-i+1);
    return x;
}
int main(){
    for(phi[1]=u[1]=1,i=2;i<M;i++){//线性筛
        if(!f[i])p[++t]=i,phi[i]=i-1,u[i]=-1;
        for(j=1;j<=t&&i*p[j]<M;j++){
            f[i*p[j]]=1;
            if(i%p[j]==0){u[p[j]*i]=0;phi[i*p[j]]=phi[i]*p[j];break;}
            phi[i*p[j]]=phi[i]*(p[j]-1);u[p[j]*i]=-u[i];
        }
    }
    for(i=2;i<M;i++)u[i]+=u[i-1],phi[i]+=phi[i-1];//预处理计算前缀和
    scanf("%lld",&x);
    printf("%lld %lld\n",P(x),U(x));
}
