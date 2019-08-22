LL Pw(LL a,LL b,LL p){//简单的非递归写法
    LL v=1;//一开始答案为1
    for(;b;){
        if(b&1)v=v*a%p;//如果b的第i位为1，那么给答案乘以a^(2^i)
        a=a*a%p;//每次a自乘，简单地求出a^(2^i)
        b>>=1;//b右移一位，判断下一位
    }
    return v;//返回答案
}
