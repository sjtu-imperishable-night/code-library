for(i=0;i<=n;i++)
    for(c[i][0]=1,j=1;j<=n;j++)
        c[i][j]=(c[i-1][j]+c[i-1][j-1])%M;
