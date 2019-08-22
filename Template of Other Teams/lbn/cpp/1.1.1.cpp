void ins(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}
void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
void ins(int x,int y){V[x].push_back(y);}
