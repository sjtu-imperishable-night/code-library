LL gcd(LL a,LL b){//递归实现
    return b?gcd(b,a%b):a;
}
LL gcd(LL a,LL b){//非递归实现
    for(LL t;b;)t=a%b,a=b,b=t;
    return a;
}
