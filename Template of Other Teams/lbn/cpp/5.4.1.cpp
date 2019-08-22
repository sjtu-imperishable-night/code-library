//试除法
for(i=1;p[i]*p[i]<=n;i++)//p[i]为预处理的质数
    for(n%p[i]==0;n/=p[i])q[++t]=p[i];
//试除法优化
if(n>1)q[++t]=p[i];for(i=2;i*i<=n;i++)
    for(;n%i==0;n/=i)q[++t]=i;//分解质因数
if(n>1)q[++t]=n;//如果n>1还需分解
