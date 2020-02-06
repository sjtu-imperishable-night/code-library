#include<bits/stdc++.h>
#define N 12121
using namespace std;bool vis[N];multiset<int>A[N],B[N],C[N];
//A记录往下以该点为根下面每个点到它的距离，B记录每个点最小的两个A，C记录全局最小值
struct W{
    multiset<int>A,B;
    int G(){
        if(A.size()<2)return 1e9;int x=*A.begin();
        multiset<int>::iterator it=A.begin();return x+(*++it);
    }
};map<int,W>mp[N];map<int,W>::iterator it;multiset<int>U;
int n,m,i,j,x,y,z,rt,tot,id,c[N],d[N],h[N],fir[N],ne[N*2],la[N*2],va[N*2],F[N][14],mv[N],sz[N],fa[N],q[N];
void D(multiset<int>&S,int x){S.erase(S.find(x));}
void ins(int x,int y,int z){la[++tot]=y;va[tot]=z;ne[tot]=fir[x];fir[x]=tot;}
void dfs(int x,int fa){//DFS预处理LCA
    for(int i=1;i<14;i++)F[x][i]=F[F[x][i-1]][i-1];
    for(int i=fir[x],y;i;i=ne[i])if(la[i]!=fa)F[y=la[i]][0]=x,h[y]=h[x]+1,d[y]=d[x]+va[i],dfs(y,x);
}
int lca(int x,int y){
    if(h[x]<h[y])swap(x,y);int t=h[x]-h[y],i;
    for(i=0;i<14;i++)if(t>>i&1)x=F[x][i];
    for(i=13;i>=0;i--)if(F[x][i]!=F[y][i])x=F[x][i],y=F[y][i];
    return x==y?x:F[x][0];
}
int dis(int x,int y){return d[x]+d[y]-2*d[lca(x,y)];}
void dsz(int x,int fa){
    sz[x]=1;mv[x]=0;
    for(int i=fir[x],y;i;i=ne[i])if(!vis[y=la[i]]&&y!=fa)dsz(y,x),sz[x]+=sz[y],mv[x]=max(mv[x],sz[y]);
}
void drt(int zs,int x,int fa,int &rt){
    mv[x]=max(mv[x],sz[zs]-sz[x]);if(mv[x]<mv[rt]||!rt)rt=x;
    for(int i=fir[x];i;i=ne[i])if(!vis[y=la[i]]&&y!=fa)drt(zs,y,x,rt);
}
void get(int x,int fa,int z,int rt){//预处理求出每个根下面的所有点到它的距离
    if(mp[rt].count(c[x]))mp[rt][c[x]].A.insert(z);else {W o;o.A.insert(z);mp[rt][c[x]]=o;}
    for(int i=fir[x],y;i;i=ne[i])if(!vis[y=la[i]]&&y!=fa)get(y,x,z+va[i],rt);
}
int fz(int x){//分治点x所在的还未被选的点
    int i,p,rt=0;dsz(x,0);drt(x,x,0,rt);vis[rt]=1;
    for(get(rt,0,0,rt),it=mp[rt].begin();it!=mp[rt].end();it++)
	it->second.B.insert(it->second.G());//每种颜色先选两个距离最小的作为B，这个答案可能不对
    for(i=fir[rt];i;i=ne[i])if(!vis[la[i]])
	for(p=fz(la[i]),fa[p]=rt,it=mp[p].begin();it!=mp[p].end();it++)
		mp[rt][it->first].B.insert(*(it->second.B.begin()));//每个根下面的每个子树记一个最小的B
    return rt;
}
void add(int x,int z,int lx){//x为点，z为颜色，lx为0时是删除，1时是加入
    if(mp[rt].count(z))D(U,*mp[rt][z].B.begin());//先删去B，中间处理A，最后加上B
    int t=0,u=x,i;
    for(;u;u=fa[u])q[++t]=u;
    for(i=t;i>1;i--)if(mp[q[i-1]].count(z))D(mp[q[i]][z].B,*mp[q[i-1]][z].B.begin());
    if(lx)for(i=1;i<=t;i++)if(mp[q[i]].count(z))D(mp[q[i]][z].B,mp[q[i]][z].G());
    for(i=x;i;i=u){
        if(lx)mp[i][z].A.insert(dis(x,i));else D(mp[i][z].B,mp[i][z].G()),D(mp[i][z].A,dis(x,i));
        mp[i][z].B.insert(mp[i][z].G());if(u=fa[i])mp[u][z].B.insert(*mp[i][z].B.begin());
    }
    U.insert(*mp[rt][z].B.begin());//更改好A后更新B
}
int main(){
    for(scanf("%d",&n),i=1;i<=n;i++)scanf("%d",&c[i]);
    for(i=1;i<n;i++)scanf("%d%d%d",&x,&y,&z),ins(x,y,z),ins(y,x,z);
    for(dfs(1,0),rt=fz(1),it=mp[rt].begin();it!=mp[rt].end();it++)U.insert(*(it->second.B.begin()));
    for(printf("%d\n",*(U.begin())),scanf("%d",&m);m--;printf("%d\n",*(U.begin())))
	scanf("%d%d",&x,&y),add(x,c[x],0),add(x,y,1),c[x]=y;
}
