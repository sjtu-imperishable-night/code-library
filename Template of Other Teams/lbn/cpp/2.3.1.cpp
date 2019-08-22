void add(int x,int z){for(;x<=n;x+=x&-x)c[x]+=z;}
int qu(int x){int v=0;for(;x;x-=x&-x)v+=c[x];return v;}
