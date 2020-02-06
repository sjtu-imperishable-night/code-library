int df(int k1,int k,int l,int r,int x,int y,int w){
    if(x<=l&&r<=y)return v[w][k1][k];
    int md=l+r>>1,ans=la[w][k1][k];
    if(x<=md)ans=max(ans,df(k1,k<<1,l,md,x,y,w));
    if(y>md)ans=max(ans,df(k1,k<<1|1,md+1,r,x,y,w));
    return ans;
}
int fd(int k,int l,int r,int x,int y,int a,int b){//区间查询最大值 
    if(x<=l&&r<=y)return df(k,1,1,S,a,b,0);
    int md=l+r>>1,ans=df(k,1,1,S,a,b,1);
    if(x<=md)ans=max(ans,fd(k<<1,l,md,x,y,a,b));
    if(y>md)ans=max(ans,fd(k<<1|1,md+1,r,x,y,a,b));
    return ans;
}
void da(int k1,int k,int l,int r,int x,int y,int z,int w){
    v[w][k1][k]=max(v[w][k1][k],z);
    if(x<=l&&r<=y){la[w][k1][k]=max(la[w][k1][k],z);return;}
    int md=l+r>>1;
    if(x<=md)da(k1,k<<1,l,md,x,y,z,w);
    if(y>md)da(k1,k<<1|1,md+1,r,x,y,z,w);
}
void add(int k,int l,int r,int x,int y,int a,int b,int z){//区间赋值 
    da(k,1,1,S,a,b,z,0);
    if(x<=l&&r<=y){da(k,1,1,S,a,b,z,1);return;}
    int md=l+r>>1;
    if(x<=md)add(k<<1,l,md,x,y,a,b,z);
    if(y>md)add(k<<1|1,md+1,r,x,y,a,b,z);
}
