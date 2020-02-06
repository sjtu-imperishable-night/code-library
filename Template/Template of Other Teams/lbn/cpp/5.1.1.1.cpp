LL Mul(LL a,LL b,LL p){//简单的非递归写法
    LL v=0;//一开始答案为0
    for(;b;){
        if(b&1)v=v*a%p;//如果b的第i位为1，那么给答案乘以(2^i)a
        a=(a+a)%p;//每次a自加，简单地求出(2^i)a
        b>>=1;//b右移一位，判断下一位
    }
    return v;//返回答案
}
LL Mul(LL a,LL b,LL p){//O(1)LL*LL%LL，保证a和b非负
	LL t=(a*b-LL((long double)a/p*b+1e-3)*p)%p;
	return t<0?t+P:t;
}
