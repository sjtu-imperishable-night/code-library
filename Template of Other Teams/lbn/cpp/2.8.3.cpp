#include<bits/stdc++.h>//BZOJ4066，插入、区间查询 
#define inf 1e9
#define N 211111
using namespace std;
struct Tree{int d[2],mn[2],mx[2],l,r,D,size,sum,v;}t[N],now;
int m,n,X1,X2,Y1,Y2,D,w,cnt,tot,ans,root,p[N];char ch;
#define L t[x].l
#define R t[x].r
int read(){
    int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;
}
inline bool cmp(int x,int y){return t[x].d[D]<t[y].d[D];}
inline void pushup(int x){
    for(int i=0;i<=1;i++)
	t[x].mn[i]=min(t[x].mn[i],min(t[L].mn[i],t[R].mn[i])),t[x].mx[i]=max(t[x].mx[i],max(t[L].mx[i],t[R].mx[i]));
    t[x].sum=t[L].sum+t[R].sum+t[x].v;
    t[x].size=t[L].size+t[R].size+1;
}
inline int build(int l,int r,int fx){
    D=fx;
    int mid=(l+r)>>1;nth_element(p+l,p+mid,p+r+1,cmp);
    int x=p[mid];t[x].D=fx;
    for(int i=0;i<2;i++)t[x].mn[i]=t[x].mx[i]=t[x].d[i];
    t[x].sum=t[x].v;
    if(l<mid)L=build(l,mid-1,fx^1);else L=0;
    if(r>mid)R=build(mid+1,r,fx^1);else R=0;
    pushup(x);return x;
}
inline void dfs(int x){if(!x)return;dfs(L);p[++cnt]=x;dfs(R);}
inline void rebuild(int &x){//重建
    cnt=0;dfs(x);x=build(1,cnt,t[x].D);}
inline void ins(int &x,int fx){
    if(!x){//新建节点
        x=++tot;t[x]=now;
        for(int i=0;i<2;i++)t[x].mn[i]=t[x].mx[i]=t[x].d[i];
        t[x].D=fx;t[x].size=1;t[x].sum=t[x].v;
        return;
    }
    if(now.d[fx]<t[x].d[fx]){
        ins(L,fx^1);
        pushup(x);
        if((double)t[L].size>(double)t[x].size*0.7)rebuild(x);
    }else{
        ins(R,fx^1);
        pushup(x);
        if((double)t[R].size>(double)t[x].size*0.7)rebuild(x);
    }
}
int query(int x,int X1,int Y1,int X2,int Y2){
	if(!x)return 0;
	if(t[x].mn[0]>=X1&&t[x].mn[1]>=Y1&&t[x].mx[0]<=X2&&t[x].mx[1]<=Y2)return t[x].sum;
	else{//包含整个区间
		int ans=0;
		if(t[x].d[0]>=X1&&t[x].d[0]<=X2&&t[x].d[1]>=Y1&t[x].d[1]<=Y2)ans+=t[x].v;//包含这个点
		if(t[L].mn[0]>X2||t[L].mx[0]<X1||t[L].mn[1]>Y2||t[L].mx[1]<Y1);else ans+=query(L,X1,Y1,X2,Y2);
		if(t[R].mn[0]>X2||t[R].mx[0]<X1||t[R].mn[1]>Y2||t[R].mx[1]<Y1);else ans+=query(R,X1,Y1,X2,Y2);
 		return ans;
	}
}
int main(){
    for(int i=0;i<=1;i++)t[0].mn[i]=inf,t[0].mx[i]=-inf;
    t[0].size=t[0].sum=t[0].v=0;n=read();
    while(scanf("%d",&w)!=EOF&&w<3)
        if(w==1){
            now.d[0]=read()^ans;now.d[1]=read()^ans;now.v=read()^ans;
            ins(root,1);
        }else{
            X1=read()^ans;Y1=read()^ans;X2=read()^ans;Y2=read()^ans;
            printf("%d\n",ans=query(root,X1,Y1,X2,Y2));
        }
}
