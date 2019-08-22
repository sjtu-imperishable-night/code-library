void exgcd(LL a,LL b,LL&x,LL&y,LL&d){//求ax+by=gcd(a,b)的可行解
    if(!b)x=1,y=0,d=a;else//若b=0，那么x=1,y=0是一组可行解，a为最大公约数
    exgcd(b,a%b,y,x,d),//递归求解
    y-=a/b*x;//gcd(a,b)=ya+(x-(a/b)y)b
}
