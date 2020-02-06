LL C(int n,int m){
    return pw[n]*I[n-m]%M*I[m]%M;
}
for(pw[0]=i=1;i<=n;i++)pw[i]=1ll*pw[i-1]*i%M;
for(I[1]=1,i=2;i<=n;i++)I[i]=1ll*(M-M/i)*I[M%i]%M;
for(i=2;i<=n;i++)I[i]=1ll*I[i]*I[i-1]%M;
