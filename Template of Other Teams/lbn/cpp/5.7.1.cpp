LL bsgs(LL a,LL b,LL p){
    LL m=ceil(sqrt(p)),v=pow(pow(a,m,p),p-2,p),i,e=1;map<LL,LL>mp;mp[1]=0;
    for(i=1;i<m;i++)if(!mp.count(e=e*a%p))mp[e]=i;
    for(i=0;i<m;b=b*v%p,i++)if(mp.count(b))return i*m+mp[b];
    return -2;
}
