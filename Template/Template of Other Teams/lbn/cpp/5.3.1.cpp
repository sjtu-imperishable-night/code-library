for(i=2;i<=n;i++)
    if(!f[i])//f[i]=0，是质数
        for(j=i*i;j<=n;j+=i)f[j]=1;//从i*i开始筛，标记为非素数
