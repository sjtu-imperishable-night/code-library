LL CRT(int n,LL a[],LL m[]){
    LL M=1,W,x,y,an=0;int i;
    for(i=1;i<=n;i++)M*=m[i];//ai为余数，mi为模数，M为模数之乘积
    for(i=1;i<=n;i++){
        W=M/m[i];//W为模数之积M除以目前模数mi
        exgcd(W,m[i],x,y);//求W在模w[i]意义下的逆元x
        an=(an+x*W%M*a[i])%M;//统计答案，注意有时候要__int128甚至高精度
    }
    return (an+M)%M;//注意返回正数
}
