namespace Fast_Read{
    const int SIZE=1<<16;
    char buf[SIZE],c;
    int l=0,r=0;
    inline char readchar(){
        if(l==r){l=0,r=fread(buf,1,SIZE,stdin);}
        return buf[l++];
    }
    inline void scanf(int&x){
        while((c=readchar())<48);
        x=c-48;
        while((c=readchar())>47)x=x*10+c-48;
    }
}
