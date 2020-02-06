bool merge(LL a1,LL m1,LL a2,LL m2,LL&A,LL&M){//将两个方程合并为一个方程 
    LL c=a2-a1,d=gcd(m1,m2);
    if(c%d)return 0;//gcd(m1,m2)|(a2-a1)时才有解 
    c=(c%m2+m2)%m2;//将c变为[0,m2)之间的数 
    c/=d;m1/=d;m2/=d;//等式两端同除d 
    c=c*inv(m1,m2)%m2;//将m1/d移到右边 
    M=m1*m2*d;//M=m1m2/d，因m1和m2都已经除d，故*d 
    A=(c*m1%M*d%M+a1)%M;//A=Km1，目前m1已经除d，故*d 
    return 1;
}
LL CRT(int n,LL a[],LL m[]){
    LL a1=a[1],m1=m[1],A,M;
    for(int i=2;i<=n;i++){
        if(!merge(a1,m1,a[i],m[i],A,M))//合并两个方程 
            return -1;//不合法 
        a1=A;m1=M;//更新目前的a1和m1 
    }
    return (a1+m1)%m1;//返回[0,m1)之间的数 
}
