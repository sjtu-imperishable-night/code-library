bool ins(LL x){//插入一个数 
    for(int i=60;~i;i--)if(x>>i&1){
        if(!d[i]){//这一位还没有线性基 
            d[i]=x;//将x加入到线性基中 
            break;//然后退出 
        }
        x^=d[i];//否则x xor d[i] 
    }
    return x>0;//判断是否插入 
}
LL qmax(){//询问最大值 
    LL V=0;
    for(int i=60;~i;i--)//从高位到低位 
        if((V^d[i])>V)V^=d[i];//如果能更大，就更大 
    return V;
}
LL qmin(){//询问最小值 
    for(int i=0;i<=60;i++)
        if(d[i])return d[i];//最低位的线性基 
    return 0;
}
bool ok(LL x){//判断x是否存在于线性基中 
    for(int i=60;~i;i--){//从高位到低位 
        x^=d[i];//每次xor d[i] 
        if(!x)return 1;//如果x变为0就存在 
    }
    return 0;
}
