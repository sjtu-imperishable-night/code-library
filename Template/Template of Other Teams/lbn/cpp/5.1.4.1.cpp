LL inv(LL a,LL n){//求a关于模数n的逆元
    LL d,x,y;
    exgcd(a,n,x,y,d);//如果(a,n)=1有逆元
    return d==1?(x+n)%n:-1;//如果x是负数对其调整
}
