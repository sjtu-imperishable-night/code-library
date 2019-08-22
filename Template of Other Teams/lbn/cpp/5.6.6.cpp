bitset<2222>a[2222];//压位
void gauss(int n,int m){
    int i,j,k;
    for(i=1;i<=n;i++){
        for(j=1;j<=m&&!a[j][i];j++);//找到a(j,i)不为0的行
        if(j>n)continue;
        if(j!=i)swap(a[i],a[j]);//交换
        for(j=i+1;j<=n;j++)//处理其它行
            if(a[j][i])a[j]^=a[i];
    }
}
