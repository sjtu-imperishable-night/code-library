LL phi(LL n){//O(n^0.5)
    LL i,V=n;//一开始赋V=n
    for(i=2;i*i<=n;i++)//i>sqrt(n)时退出，优化复杂度
        if(n%i==0)//对pi^ki，将其变为pi^(ki-1)*(pi-1)
            for(V=V/i*(i-1);n%i==0;)n/=i;//分解质因数
    if(n>1)V=V/n*(n-1);//剩下一个是质数
    return V;
}
